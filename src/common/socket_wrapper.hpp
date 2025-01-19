#pragma once
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdexcept>
#include <string>

namespace ecuafast {
class SocketWrapper {
 public:
  static int createServerSocket(int port) {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
      throw std::runtime_error("Failed to create socket");
    }

    // Allow port reuse
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) <
        0) {
      close(serverSocket);
      throw std::runtime_error("Failed to bind socket");
    }

    if (listen(serverSocket, 10) < 0) {
      close(serverSocket);
      throw std::runtime_error("Failed to listen on socket");
    }

    return serverSocket;
  }

  static int createClientSocket(const std::string& host, int port) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
      throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr) <= 0) {
      close(clientSocket);
      throw std::runtime_error("Invalid address");
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddr,
                sizeof(serverAddr)) < 0) {
      close(clientSocket);
      throw std::runtime_error("Connection failed");
    }

    return clientSocket;
  }
};
}  // namespace ecuafast