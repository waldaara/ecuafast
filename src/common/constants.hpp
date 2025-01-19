#pragma once

namespace ecuafast {
namespace constants {
constexpr int DEFAULT_PORT_SRI = 8080;
constexpr int DEFAULT_PORT_SENAE = 8081;
constexpr int DEFAULT_PORT_SUPERCIA = 8082;
constexpr int DEFAULT_PORT_MANAGER = 8083;
constexpr const char* DEFAULT_HOST = "127.0.0.1";

// Response types
constexpr const char* RESPONSE_PASS = "PASS";
constexpr const char* RESPONSE_CHECK = "CHECK";
constexpr const char* RESPONSE_ACCEPTED = "ACCEPTED";
constexpr const char* RESPONSE_REJECTED = "REJECTED";
}  // namespace constants
}  // namespace ecuafast