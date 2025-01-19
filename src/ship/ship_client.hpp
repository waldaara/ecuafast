#pragma once
#include "../common/constants.hpp"
#include "../common/socket_wrapper.hpp"
#include "../common/types.hpp"

namespace ecuafast {
class ShipClient {
 public:
  ShipClient(const ShipInfo& info, int timeout);
  void start();

  std::string connectToEntity(int port);

 private:
  ShipInfo info;
  int timeout;
  int portManagerClientSocket;

  bool requestInspection();
  bool requestDocking();
  void doInspection();
};
}  // namespace ecuafast