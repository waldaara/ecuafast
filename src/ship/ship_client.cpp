#include "ship_client.hpp"

#include <bits/this_thread_sleep.h>

#include <future>
#include <iostream>

namespace ecuafast {

ShipClient::ShipClient(const ShipInfo& info, int timeout)
    : info(info), timeout(timeout) {
  try {
    portManagerClientSocket = SocketWrapper::createClientSocket(
        constants::DEFAULT_HOST, constants::DEFAULT_PORT_MANAGER);
  } catch (const std::exception& e) {
    std::cerr << "Ship " << info.id << " error: " << e.what() << "\n";
  }
}

void ShipClient::start() {
  try {
    std::vector<std::future<bool>> responses;

    // Request for inspection and docking in parallel
    responses.push_back(std::async(std::launch::async,
                                   [this]() { return requestInspection(); }));
    responses.push_back(
        std::async(std::launch::async, [this]() { return requestDocking(); }));

    bool needInspection = responses.at(0).get();
    bool canDock = responses.at(1).get();

    if (needInspection && canDock) {
      doInspection();
    }

  } catch (const std::exception& e) {
    std::cerr << "Ship " << info.id << " error: " << e.what() << "\n";
  }
}

std::string ShipClient::connectToEntity(int port) {
  try {
    int clientSocket =
        SocketWrapper::createClientSocket(constants::DEFAULT_HOST, port);

    // Send ship info
    nlohmann::json jsonShip = info.to_json();
    std::string jsonStr = jsonShip.dump();
    send(clientSocket, jsonStr.c_str(), jsonStr.length(), 0);

    // Receive response
    char buffer[1024] = {0};
    read(clientSocket, buffer, sizeof(buffer));

    close(clientSocket);
    return std::string(buffer);

  } catch (const std::exception& e) {
    std::cerr << "Ship " << info.id << " error: " << e.what() << "\n";
    return "";
  }
}

bool ShipClient::requestInspection() {
  std::cout << "Ship " << info.id << " starting inspection request\n";

  int checkCount = 0;

  while (true) {
    checkCount = 0;
    std::vector<std::future<std::string>> responses;

    // Connect to all three entities in parallel
    responses.push_back(std::async(std::launch::async, [this]() {
      return connectToEntity(constants::DEFAULT_PORT_SRI);
    }));
    responses.push_back(std::async(std::launch::async, [this]() {
      return connectToEntity(constants::DEFAULT_PORT_SENAE);
    }));
    responses.push_back(std::async(std::launch::async, [this]() {
      return connectToEntity(constants::DEFAULT_PORT_SUPERCIA);
    }));

    bool allResponsesReceived = true;

    // Wait for responses with timeout
    for (auto& future : responses) {
      if (future.wait_for(std::chrono::seconds(timeout)) ==
          std::future_status::ready) {
        std::string response = future.get();

        if (response == constants::RESPONSE_CHECK) {
          checkCount++;
        }
      } else {
        // A response timed out; retry the whole process
        allResponsesReceived = false;
        break;
      }
    }

    // If all responses are received and at least 2 are valid, return success
    if (allResponsesReceived) {
      info.needsInspection = checkCount >= 2;

      std::cout << "Ship " << info.id
                << (info.needsInspection ? " requires" : " does not require")
                << " inspection\n";

      return info.needsInspection;
    }

    // Log the retry attempt
    std::cerr << "Timeout occurred. Retrying request inspection for ship "
              << info.id << "\n";
  }
}

bool ShipClient::requestDocking() {
  std::cout << "Ship " << info.id << " starting docking request\n";

  // Send docking request
  nlohmann::json jsonShip = info.to_json();
  std::string jsonStr = jsonShip.dump();  // Convert to JSON string

  send(portManagerClientSocket, jsonStr.c_str(), jsonStr.length(), 0);

  // Receive response
  char buffer[1024] = {0};
  read(portManagerClientSocket, buffer, sizeof(buffer));

  bool canDock = std::string(buffer) == constants::RESPONSE_ACCEPTED;

  return canDock;
}

void ShipClient::doInspection() {
  // Send docking request
  nlohmann::json jsonShip = info.to_json();
  std::string jsonStr = jsonShip.dump();  // Convert to JSON string

  send(portManagerClientSocket, jsonStr.c_str(), jsonStr.length(), 0);
}

}  // namespace ecuafast
