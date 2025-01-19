#pragma once
#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

#include "../common/constants.hpp"
#include "../common/socket_wrapper.hpp"
#include "../common/types.hpp"
#include "../common/utils.hpp"

namespace ecuafast {
class PortManager {
 public:
  PortManager(int port, int maxSlots, double damageProb, int unloadTime);
  void start();
  bool requestDocking(int clientSocket, const ShipInfo& ship);
  void releaseSlot(int shipId);

 private:
  std::list<PortSlot> dockingSlots;
  std::mutex slotsMutex;
  std::condition_variable slotsCV;
  std::vector<std::thread> workerThreads;
  bool shutdown = false;
  int maxSlots;
  double damageProb;
  int unloadTime;
  int port;

  void handleDamageEvent();
  void handleClient(int clientSocket);
  void processQueue();
  void doInspection(const ShipInfo& ship);
};
}  // namespace ecuafast