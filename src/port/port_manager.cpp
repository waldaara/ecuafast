#include "port_manager.hpp"

#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>

namespace ecuafast {

PortManager::PortManager(int port, int maxSlots, double damageProb,
                         int unloadTime)
    : port(port),
      maxSlots(maxSlots),
      damageProb(damageProb),
      unloadTime(unloadTime),
      shutdown(false) {
  dockingSlots.resize(maxSlots, {false, nullptr, 0, 0});

  // Initialize worker threads
  for (int i = 0; i < maxSlots; ++i) {
    workerThreads.emplace_back([this]() { processQueue(); });
  }
}

void PortManager::start() {
  int serverSocket = SocketWrapper::createServerSocket(port);

  while (!shutdown) {
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

  // Cleanup
  for (auto& thread : workerThreads) {
    thread.join();
  }
}

bool PortManager::requestDocking(int clientSocket, const ShipInfo& ship) {
  std::lock_guard<std::mutex> lock(slotsMutex);

  // std::cout << "Received docking request for " << ship.id << "\n";

  // Just check if any slot is available
  auto availableSlot =
      std::find_if(dockingSlots.begin(), dockingSlots.end(),
                   [](const PortSlot& slot) { return !slot.occupied; });

  return availableSlot != dockingSlots.end();
}

void PortManager::doInspection(const ShipInfo& ship) {
  std::cout << "Ship " << ship.id << " starting inspection\n";

  std::lock_guard<std::mutex> lock(slotsMutex);

  // Find first empty slot
  auto emptySlot =
      std::find_if(dockingSlots.begin(), dockingSlots.end(),
                   [](const PortSlot& slot) { return !slot.occupied; });

  if (emptySlot != dockingSlots.end()) {
    // Only mark as occupied and set the ship info
    emptySlot->occupied = true;
    emptySlot->ship = new ShipInfo(ship);
    emptySlot->arrivalTime = std::time(nullptr);
    emptySlot->departureTime = 0;  // Will be set by processQueue
  }

  // Notify one worker that new work is available
  slotsCV.notify_one();
}

void PortManager::processQueue() {
  while (!shutdown) {
    ShipInfo* shipToProcess = nullptr;
    std::list<PortSlot>::iterator slotToProcess;

    // Wait for work
    {
      std::unique_lock<std::mutex> lock(slotsMutex);
      slotsCV.wait(lock, [this]() {
        return shutdown || std::any_of(dockingSlots.begin(), dockingSlots.end(),
                                       [](const PortSlot& slot) {
                                         return slot.occupied &&
                                                slot.ship != nullptr &&
                                                slot.departureTime == 0;
                                       });
      });

      if (shutdown) {
        return;
      }

      // First look for priority ships that haven't been processed
      auto it = std::find_if(
          dockingSlots.begin(), dockingSlots.end(), [](const PortSlot& slot) {
            return slot.occupied && slot.ship != nullptr &&
                   slot.departureTime == 0 &&  // Not yet processed
                   slot.ship->needsInspection &&
                   slot.ship->destination != "Ecuador";
          });

      // If no priority ships, get first unprocessed ship
      if (it == dockingSlots.end()) {
        it = std::find_if(
            dockingSlots.begin(), dockingSlots.end(), [](const PortSlot& slot) {
              return slot.occupied && slot.ship != nullptr &&
                     slot.departureTime == 0;  // Not yet processed
            });
      }

      if (it != dockingSlots.end()) {
        slotToProcess = it;
        shipToProcess = it->ship;

        // Calculate processing time
        int processTime = unloadTime;
        if (shipToProcess->destination != "Ecuador") {
          processTime /= 2;
        }
        if (shipToProcess->needsInspection) {
          processTime *= 2;
        }

        // Set departure time to mark as being processed
        it->departureTime = it->arrivalTime + processTime;
      }
    }

    if (shipToProcess) {
      int processTime =
          slotToProcess->departureTime - slotToProcess->arrivalTime;

      std::cout << "Ship " << shipToProcess->id << " starting unload process ("
                << processTime << " seconds)\n";

      // Simulate processing time
      std::this_thread::sleep_for(std::chrono::seconds(processTime));

      std::cout << "Ship " << shipToProcess->id << " finished unloading\n";

      // Release the slot
      releaseSlot(shipToProcess->id);
    }
  }
}

void PortManager::releaseSlot(int shipId) {
  std::lock_guard<std::mutex> lock(slotsMutex);

  auto it = std::find_if(
      dockingSlots.begin(), dockingSlots.end(), [shipId](const PortSlot& slot) {
        return slot.occupied && slot.ship != nullptr && slot.ship->id == shipId;
      });

  if (it != dockingSlots.end()) {
    std::cout << "Releasing slot for ship " << shipId << "\n";
    delete it->ship;
    it->ship = nullptr;
    it->occupied = false;
    it->arrivalTime = 0;
    it->departureTime = 0;
  }

  slotsCV.notify_all();
}

void PortManager::handleDamageEvent() {
  std::lock_guard<std::mutex> lock(slotsMutex);

  auto it = std::find_if(dockingSlots.begin(), dockingSlots.end(),
                         [](const PortSlot& slot) { return slot.occupied; });

  if (it != dockingSlots.end()) {
    delete it->ship;
    it->ship = nullptr;
    it->occupied = false;
    std::rotate(it, std::next(it), dockingSlots.end());
  }
}

void PortManager::handleClient(int clientSocket) {
  char buffer[1024] = {0};  // Initialize buffer to zero
  ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));

  int shipId;

  if (bytesRead > 0) {
    auto j = nlohmann::json::parse(buffer);
    ShipInfo ship = ShipInfo::from_json(j);
    shipId = ship.id;

    bool responseBool = requestDocking(clientSocket, ship);
    std::string responseStr = responseBool ? constants::RESPONSE_ACCEPTED
                                           : constants::RESPONSE_REJECTED;
    send(clientSocket, responseStr.c_str(), responseStr.length(), 0);

    if (!responseBool) {
      close(clientSocket);
      return;
    }
  }

  if (utils::generateRandomProbability() < damageProb) {
    handleDamageEvent();
    std::cout << "Ship " << shipId << " is broken and was removed\n";
    close(clientSocket);
    return;
  }

  memset(buffer, 0, sizeof(buffer));  // Clear buffer before second read
  bytesRead = read(clientSocket, buffer, sizeof(buffer));

  if (bytesRead > 0) {
    auto j = nlohmann::json::parse(buffer);
    ShipInfo ship = ShipInfo::from_json(j);
    doInspection(ship);
  }

  close(clientSocket);
}

}  // namespace ecuafast