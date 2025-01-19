#include <getopt.h>

#include <iostream>
#include <thread>
#include <vector>

#include "common/constants.hpp"
#include "common/types.hpp"
#include "common/utils.hpp"
#include "entities/senae_server.hpp"
#include "entities/sri_server.hpp"
#include "entities/supercia_server.hpp"
#include "port/port_manager.hpp"
#include "ship/ship_client.hpp"

void printUsage() {
  std::cout << "Usage: ecuafast [options]\n"
            << "Options:\n"
            << "  -x SECONDS   Timeout for entity responses\n"
            << "  -y SECONDS   Base unloading time\n"
            << "  -z COUNT     Number of ships to simulate\n"
            << "  -n COUNT     Maximum number of port slots\n"
            << "  -p PROB      Probability of ship damage (0.0-1.0)\n";
}

int main(int argc, char* argv[]) {
  int timeout = 4;
  int unloadTime = 5;
  int shipCount = 10;
  int maxSlots = 5;
  double damageProb = 0.2;

  int opt;
  while ((opt = getopt(argc, argv, "x:y:z:n:p:h")) != -1) {
    switch (opt) {
      case 'x':
        timeout = std::atoi(optarg);
        break;
      case 'y':
        unloadTime = std::atoi(optarg);
        break;
      case 'z':
        shipCount = std::atoi(optarg);
        break;
      case 'n':
        maxSlots = std::atoi(optarg);
        break;
      case 'p':
        damageProb = std::atof(optarg);
        break;
      case 'h':
        printUsage();
        return 0;
      default:
        printUsage();
        return 1;
    }
  }

  try {
    // Start control entities
    ecuafast::SRIServer sri(ecuafast::constants::DEFAULT_PORT_SRI);
    ecuafast::SENAEServer senae(ecuafast::constants::DEFAULT_PORT_SENAE);
    ecuafast::SuperCIAServer supercia(
        ecuafast::constants::DEFAULT_PORT_SUPERCIA);

    std::thread sriThread([&sri]() { sri.start(); });
    std::thread senaeThread([&senae]() { senae.start(); });
    std::thread superciaThread([&supercia]() { supercia.start(); });

    // Start port manager
    ecuafast::PortManager portManager(ecuafast::constants::DEFAULT_PORT_MANAGER,
                                      maxSlots, damageProb, unloadTime);
    std::thread portThread([&portManager]() { portManager.start(); });

    // Create and start ships
    std::vector<std::thread> shipThreads;
    for (int i = 0; i < shipCount; ++i) {
      ecuafast::ShipInfo info{
          static_cast<ecuafast::ShipType>(
              ecuafast::utils::generateRandomProbability() > 0.5),
          50000 + ecuafast::utils::generateRandomProbability() * 50000,
          ecuafast::utils::generateRandomProbability() > 0.5
              ? "Ecuador"
              : (ecuafast::utils::generateRandomProbability() > 0.5 ? "USA"
                                                                    : "Europe"),
          i, false};

      shipThreads.emplace_back([info, timeout]() {
        ecuafast::ShipClient ship(info, timeout);
        ship.start();
      });
    }

    // Wait for all ships to finish
    for (auto& thread : shipThreads) {
      thread.join();
    }

    std::cout << "Simulation completed.\n";
    return 0;

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}