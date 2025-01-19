#include "supercia_server.hpp"

#include <iostream>
#include <thread>

namespace ecuafast {

SuperCIAServer::SuperCIAServer(int port) : port(port) {}

void SuperCIAServer::start() {
  int serverSocket = SocketWrapper::createServerSocket(port);

  while (true) {
    sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);
    int clientSocket =
        accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);

    if (clientSocket >= 0) {
      std::thread([this, clientSocket]() {
        this->handleClient(clientSocket);
      }).detach();
    }
  }
}

std::string SuperCIAServer::evaluateShip(const ShipInfo& ship) {
  double checkProbability = (ship.type == ShipType::CONVENTIONAL) ? 0.3 : 0.5;

  if (utils::generateRandomProbability() < checkProbability) {
    return constants::RESPONSE_CHECK;
  }

  return constants::RESPONSE_PASS;
}

void SuperCIAServer::handleClient(int clientSocket) {
  char buffer[1024] = {0};
  ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));

  if (bytesRead > 0) {
    try {
      auto j = nlohmann::json::parse(buffer);
      ShipInfo ship = ShipInfo::from_json(j);
      std::string response = evaluateShip(ship);

      int response_time = utils::generateRandomDelay(1, 5);

      // Simulate random response time
      std::this_thread::sleep_for(std::chrono::seconds(response_time));

      // std::cout << "Ship " << ship.id << " got " << response << " after "
      //           << response_time << " seconds\n";

      send(clientSocket, response.c_str(), response.length(), 0);
    } catch (const std::exception& e) {
      std::cerr << "Error processing request: " << e.what() << "\n";
    }
  }

  close(clientSocket);
}

}  // namespace ecuafast