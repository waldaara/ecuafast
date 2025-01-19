cmake_minimum_required(VERSION 3.10)
project(ecuafast)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)

# Add source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.hpp"
)

# Create executable
add_executable(ecuafast ${SOURCES})

# Include directories
target_include_directories(ecuafast PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(ecuafast PRIVATE
    Threads::Threads
)

# Installation
install(TARGETS ecuafast
    RUNTIME DESTINATION bin
)