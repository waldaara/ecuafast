#pragma once
#include <chrono>
#include <random>

namespace ecuafast {
namespace utils {
inline double generateRandomProbability() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<> dis(0, 1);
  return dis(gen);
}

inline int generateRandomDelay(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}
}  // namespace utils
}  // namespace ecuafast