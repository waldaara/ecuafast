#pragma once
#include "../common/constants.hpp"
#include "../common/socket_wrapper.hpp"
#include "../common/types.hpp"
#include "../common/utils.hpp"

namespace ecuafast {
class SuperCIAServer {
 public:
  SuperCIAServer(int port);
  void start();
  std::string evaluateShip(const ShipInfo& ship);

 private:
  int port;
  void handleClient(int clientSocket);
};
}  // namespace ecuafast