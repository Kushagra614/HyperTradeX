cmake_minimum_required(VERSION 3.16)
project(HyperTradeX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler Flags
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -O2 -march=native")

# Include Directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Source Files
set(SOURCES
    src/main.cpp
    src/data_loader.cpp
    src/parser.cpp
    src/replay_engine.cpp
    src/strategy.cpp
    src/execution.cpp
    src/metrics.cpp
)

# Create Executable
add_executable(hypertradex ${SOURCES})
