#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace ecuafast {
enum class ShipType { CONVENTIONAL, PANAMAX };

struct ShipInfo {
  ShipType type;
  double avgWeight;
  std::string destination;
  int id;
  bool needsInspection;

  // Serialización a JSON
  nlohmann::json to_json() const {
    return nlohmann::json{{"type", static_cast<int>(type)},
                          {"avgWeight", avgWeight},
                          {"destination", destination},
                          {"id", id},
                          {"needsInspection", needsInspection}};
  }

  // Deserialización desde JSON
  static ShipInfo from_json(const nlohmann::json& j) {
    ShipInfo info;
    info.type = static_cast<ShipType>(j["type"].get<int>());
    info.avgWeight = j["avgWeight"].get<double>();
    info.destination = j["destination"].get<std::string>();
    info.id = j["id"].get<int>();
    info.needsInspection = j["needsInspection"].get<bool>();
    return info;
  }
};

struct PortSlot {
  bool occupied;
  ShipInfo* ship;
  time_t arrivalTime;
  time_t departureTime;
};
}  // namespace ecuafast