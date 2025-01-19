#include "sri_server.hpp"

#include <iostream>
#include <numeric>
#include <thread>

namespace ecuafast {

SRIServer::SRIServer(int port) : port(port) {}

void SRIServer::start() {
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

std::string SRIServer::evaluateShip(const ShipInfo& ship) {
  std::lock_guard<std::mutex> lock(weightsMutex);

  if (ship.type == ShipType::CONVENTIONAL &&
      ship.avgWeight > calculateAverage() && ship.destination == "Ecuador") {
    return constants::RESPONSE_CHECK;
  }

  return constants::RESPONSE_PASS;
}

double SRIServer::calculateAverage() {
  if (lastTwentyWeights.empty()) {
    return 0.0;
  }

  double sum =
      std::accumulate(lastTwentyWeights.begin(), lastTwentyWeights.end(), 0.0);
  return sum / lastTwentyWeights.size();
}

void SRIServer::handleClient(int clientSocket) {
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