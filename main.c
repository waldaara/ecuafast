#include <arpa/inet.h>
#include <bits/getopt_core.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024

// Function to start the server
void start_server(int port) {
  int server_socket, new_client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len = sizeof(client_addr);

  // Create the server socket
  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Error opening socket");
    exit(EXIT_FAILURE);
  }

  // Setup server address structure
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  // Bind the socket to the address
  if (bind(server_socket, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) < 0) {
    perror("Error binding socket");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Start listening for connections
  if (listen(server_socket, 5) < 0) {
    perror("Error listening on socket");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", port);

  // Accept and handle incoming client connections
  while (1) {
    new_client_socket =
        accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (new_client_socket < 0) {
      perror("Error accepting connection");
      continue;  // Continue listening for other clients
    }

    // Create threads to handle client commands and streaming
    // pthread_t command_thread, streaming_thread;
    // pthread_create(&command_thread, NULL, listen_commands, (void
    // *)client_data);

    // Wait for threads to finish
    // pthread_join(command_thread, NULL);

    // Clean up and close client socket
    // free(client_data);
    // close(new_client_socket);
  }

  close(server_socket);
}

int main(int argc, char *argv[]) {
  int port = DEFAULT_PORT;
  int opt;

  while ((opt = getopt(argc, argv, "p:")) != -1) {
    switch (opt) {
      case 'p':
        port = atoi(optarg);

        if (port <= 0) {
          fprintf(stderr, "Error: 'p' must be a positive integer.\n");

          return EXIT_FAILURE;
        }

        break;

      default:
        fprintf(stderr, "Usage: %s -p <port>\n", argv[0]);

        return EXIT_FAILURE;
    }
  }

  start_server(port);

  return EXIT_SUCCESS;
}
