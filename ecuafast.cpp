#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <random>
#include <chrono>
#include <condition_variable>
#include <getopt.h>
#include <list>
#include <vector>
#include <atomic>
#include <map>
#include <deque>
#include <algorithm>

struct ProgramParams {
    int X;  // Timeout seconds for control entities
    int Y;  // Base unloading time in seconds
    int Z;  // Number of ships to simulate
    int N;  // Maximum number of ships in port
    double P;  // Probability of ship damage
};

enum class ShipType {
    CONVENTIONAL,
    PANAMAX
};

enum class Response {
    PASS,
    CHECK,
    PENDING
};

struct Ship {
    int id;
    ShipType type;
    double avgWeight;
    bool destinationEcuador;
    bool needsInspection;
    std::chrono::system_clock::time_point arrivalTime;
};

class Statistics {
private:
    std::mutex mtx;
    std::deque<double> lastTwentyWeights;
    std::vector<double> allWeights;

public:
    void addWeight(double weight) {
        std::lock_guard<std::mutex> lock(mtx);
        if (lastTwentyWeights.size() >= 20) {
            lastTwentyWeights.pop_front();
        }
        lastTwentyWeights.push_back(weight);
        allWeights.push_back(weight);
    }

    double getAverage() {
        std::lock_guard<std::mutex> lock(mtx);
        if (lastTwentyWeights.empty()) return 0.0;
        double sum = 0;
        for (double w : lastTwentyWeights) {
            sum += w;
        }
        return sum / lastTwentyWeights.size();
    }

    double getThirdQuartile() {
        std::lock_guard<std::mutex> lock(mtx);
        if (allWeights.empty()) return 0.0;
        
        std::vector<double> sorted = allWeights;
        std::sort(sorted.begin(), sorted.end());
        int index = (sorted.size() * 3) / 4;
        return sorted[index];
    }
};

class Port {
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::list<Ship> dockingQueue;
    int maxShips;
    int currentShips;
    Statistics stats;

public:
    Port(int N) : maxShips(N), currentShips(0) {}

    void addShip(const Ship& ship) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = dockingQueue.begin();
        while (it != dockingQueue.end() && 
               !(ship.needsInspection && !ship.destinationEcuador && 
                 (!it->needsInspection || it->destinationEcuador))) {
            ++it;
        }
        dockingQueue.insert(it, ship);
        cv.notify_all();
    }

    bool tryDock(Ship& ship, const ProgramParams& params) {
        std::unique_lock<std::mutex> lock(mtx);
        
        while (currentShips >= maxShips || 
               (dockingQueue.front().id != ship.id)) {
            cv.wait(lock);
        }

        // Random damage check
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        if (dis(gen) < params.P) {
            std::cout << "Ship " << ship.id << " damaged during approach\n";
            dockingQueue.remove_if([&ship](const Ship& s) { 
                return s.id == ship.id; 
            });
            return false;
        }

        currentShips++;
        dockingQueue.pop_front();
        return true;
    }

    void releaseShip() {
        std::lock_guard<std::mutex> lock(mtx);
        currentShips--;
        cv.notify_all();
    }

    Statistics& getStatistics() { return stats; }
};

class ControlEntity {
protected:
    std::mutex mtx;
    std::condition_variable cv;
    std::map<int, Response> responses;
    std::queue<Ship> pending_ships;
    std::atomic<bool> running{true};
    std::string name;

public:
    ControlEntity(const std::string& n) : name(n) {}

    void submitShip(const Ship& ship) {
        std::lock_guard<std::mutex> lock(mtx);
        pending_ships.push(ship);
        cv.notify_one();
    }

    Response getResponse(int shipId, int timeoutSeconds) {
        //TODO: sleep random

        auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(timeoutSeconds);
        std::unique_lock<std::mutex> lock(mtx);
        
        while (responses.find(shipId) == responses.end()) {
            if (cv.wait_until(lock, deadline) == std::cv_status::timeout) {
                return Response::PENDING;
            }
        }
        
        Response resp = responses[shipId];
        responses.erase(shipId);
        return resp;
    }

    void processShips(Statistics& stats) {
        while (running) {
            std::unique_lock<std::mutex> lock(mtx);
            if (pending_ships.empty()) {
                cv.wait_for(lock, std::chrono::milliseconds(100), [this] { return !pending_ships.empty() || !running; });
                continue;
            }

            Ship ship = pending_ships.front();
            pending_ships.pop();
            lock.unlock();

            Response result = evaluate(ship, stats);
            
            lock.lock();
            responses[ship.id] = result;
            cv.notify_all();
            std::cout << name << " evaluated Ship " << ship.id << ": " 
                     << (result == Response::CHECK ? "CHECK" : "PASS") << std::endl;
        }
    }

    virtual Response evaluate(const Ship& ship, Statistics& stats) = 0;

    void stop() {
        running = false;
        cv.notify_all();
    }

    virtual ~ControlEntity() = default;
};

class SRI : public ControlEntity {
public:
    SRI() : ControlEntity("SRI") {}

    Response evaluate(const Ship& ship, Statistics& stats) override {
        if (ship.type == ShipType::CONVENTIONAL && 
            ship.avgWeight > stats.getAverage() && 
            ship.destinationEcuador) {
            return Response::CHECK;
        }
        return Response::PASS;
    }
};

class SENAE : public ControlEntity {
public:
    SENAE() : ControlEntity("SENAE") {}

    Response evaluate(const Ship& ship, Statistics& stats) override {
        if (ship.type == ShipType::PANAMAX && 
            ship.avgWeight >= stats.getThirdQuartile() && 
            !ship.destinationEcuador) {
            return Response::CHECK;
        }
        return Response::PASS;
    }
};

class SUPERCIA : public ControlEntity {
public:
    SUPERCIA() : ControlEntity("SUPERCIA") {}

    Response evaluate(const Ship& ship, Statistics& stats) override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        double threshold = (ship.type == ShipType::CONVENTIONAL) ? 0.3 : 0.5;
        return (dis(gen) < threshold) ? Response::CHECK : Response::PASS;
    }
};

void shipProcess(int id, Port& port, std::vector<std::shared_ptr<ControlEntity>>& entities,
                const ProgramParams& params) {
    Ship ship;
    ship.id = id;
    
    // Initialize ship properties
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> weightDis(10000, 50000);
    std::uniform_int_distribution<> typeDis(0, 1);
    std::uniform_int_distribution<> destDis(0, 1);
    
    ship.type = typeDis(gen) ? ShipType::CONVENTIONAL : ShipType::PANAMAX;
    ship.avgWeight = weightDis(gen);
    ship.destinationEcuador = destDis(gen) ? true : false;
    ship.needsInspection = false;
    ship.arrivalTime = std::chrono::system_clock::now();
    
    std::cout << "Ship " << id << " arrived (Type: " 
              << (ship.type == ShipType::CONVENTIONAL ? "CONVENTIONAL" : "PANAMAX")
              << ", Destination: " << (ship.destinationEcuador ? "Ecuador" : "International")
              << ", Weight: " << ship.avgWeight << ")\n";
    
    // Add weight to statistics
    port.getStatistics().addWeight(ship.avgWeight);
    
    // Submit to all control entities first
    // TODO: parallel?
    for (auto& entity : entities) {
        entity->submitShip(ship);
    }

    // Then wait for their responses
    int checkCount = 0;
    for (auto& entity : entities) {
        Response response = entity->getResponse(ship.id, params.X);
        if (response == Response::PENDING) {
            std::cout << "Ship " << id << " timeout from entity, retrying\n";
            return;
        }
        if (response == Response::CHECK) {
            checkCount++;
        }
    }
    
    ship.needsInspection = (checkCount >= 2);
    std::cout << "Ship " << id << (ship.needsInspection ? " requires" : " doesn't require") 
              << " inspection (received " << checkCount << " CHECKs)\n";
    
    // Try to dock
    port.addShip(ship);
    if (!port.tryDock(ship, params)) {
        return;
    }
    
    std::cout << "Ship " << id << " started unloading\n";
    
    // Calculate unloading time
    int unloadTime = params.Y;
    if (!ship.destinationEcuador) {
        unloadTime /= 2;
    }
    if (ship.needsInspection) {
        unloadTime *= 2;
    }
    
    // Simulate unloading
    std::this_thread::sleep_for(std::chrono::seconds(unloadTime));

    // Release dock
    port.releaseShip();
    std::cout << "Ship " << id << " finished unloading (in " << unloadTime <<" seconds) and left the port\n";
}

void controlEntityProcess(std::shared_ptr<ControlEntity> entity, Port& port) {
    entity->processShips(port.getStatistics());
}

void parseArgs(int argc, char* argv[], ProgramParams& params) {
    int opt;
    while ((opt = getopt(argc, argv, "x:y:z:n:p:")) != -1) {
        switch (opt) {
            case 'x': params.X = std::atoi(optarg); break;
            case 'y': params.Y = std::atoi(optarg); break;
            case 'z': params.Z = std::atoi(optarg); break;
            case 'n': params.N = std::atoi(optarg); break;
            case 'p': params.P = std::atof(optarg); break;
            default:
                std::cerr << "Usage: " << argv[0] << " -x X -y Y -z Z -n N -p P\n";
                exit(1);
        }
    }

    std::cout << "X: " << params.X << ", "
              << "Y: " << params.Y << ", "
              << "Z: " << params.Z << ", "
              << "N: " << params.N << ", "
              << "P: " << params.P << std::endl;
}

int main(int argc, char* argv[]) {
    ProgramParams params = {5, 5, 10, 5, 0.1}; // Default values
    parseArgs(argc, argv, params);
    
    Port port(params.N);
    
    // Create control entities
    std::vector<std::shared_ptr<ControlEntity>> entities;
    entities.push_back(std::make_shared<SRI>());
    entities.push_back(std::make_shared<SENAE>());
    entities.push_back(std::make_shared<SUPERCIA>());
    
    // Start control entity threads
    std::vector<std::thread> controlThreads;
    for (auto& entity : entities) {
        controlThreads.emplace_back(controlEntityProcess, entity, std::ref(port));
    }
    
    // Start ship threads
    std::vector<std::thread> shipThreads;
    for (int i = 0; i < params.Z; ++i) {
        shipThreads.emplace_back(shipProcess, i, std::ref(port), 
                                std::ref(entities), std::ref(params));
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Stagger ship arrivals
    }
    
    // Wait for ships to complete
    for (auto& thread : shipThreads) {
        thread.join();
    }
    
    // Clean up
    for (auto& thread : controlThreads) {
        thread.detach();
    }
    
    return 0;
}