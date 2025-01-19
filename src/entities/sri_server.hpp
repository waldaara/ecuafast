#pragma once
#include <mutex>
#include <vector>

#include "../common/constants.hpp"
#include "../common/socket_wrapper.hpp"
#include "../common/types.hpp"
#include "../common/utils.hpp"

namespace ecuafast {
class SRIServer {
 public:
  SRIServer(int port);
  void start();
  std::string evaluateShip(const ShipInfo& ship);

 private:
  std::vector<double> lastTwentyWeights;
  std::mutex weightsMutex;
  int port;

  double calculateAverage();
  void handleClient(int clientSocket);
};
}  // namespace ecuafast