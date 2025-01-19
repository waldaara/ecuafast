#pragma once
#include <mutex>
#include <vector>

#include "../common/constants.hpp"
#include "../common/socket_wrapper.hpp"
#include "../common/types.hpp"
#include "../common/utils.hpp"

namespace ecuafast {
class SENAEServer {
 public:
  SENAEServer(int port);
  void start();
  std::string evaluateShip(const ShipInfo& ship);

 private:
  std::vector<double> allWeights;
  std::mutex weightsMutex;
  int port;

  double calculateThirdQuartile();
  void handleClient(int clientSocket);
};
}  // namespace ecuafast