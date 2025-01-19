#include "senae_server.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>

namespace ecuafast {

SENAEServer::SENAEServer(int port) : port(port) {}

void SENAEServer::start() {
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

std::string SENAEServer::evaluateShip(const ShipInfo& ship) {
  std::lock_guard<std::mutex> lock(weightsMutex);

  if (ship.type == ShipType::PANAMAX &&
      ship.avgWeight >= calculateThirdQuartile() &&
      (ship.destination == "Europe" || ship.destination == "USA")) {
    allWeights.push_back(ship.avgWeight);
    return constants::RESPONSE_CHECK;
  }

  allWeights.push_back(ship.avgWeight);
  return constants::RESPONSE_PASS;
}

double SENAEServer::calculateThirdQuartile() {
  if (allWeights.empty()) {
    return 0.0;
  }

  std::vector<double> sortedWeights = allWeights;
  std::sort(sortedWeights.begin(), sortedWeights.end());

  size_t idx = (sortedWeights.size() * 3) / 4;
  return sortedWeights[idx];
}

void SENAEServer::handleClient(int clientSocket) {
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