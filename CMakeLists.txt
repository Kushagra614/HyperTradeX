cmake_minimum_required(VERSION 3.16)
project(HyperTradeX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CURL REQUIRED libcurl)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler Flags
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -O2 -march=native -g")

# Include Directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Source Files
set(SOURCES
    src/mainCSV.cpp
    src/data_loader.cpp
    src/parser.cpp
    src/replay_engine.cpp
    src/strategy.cpp
    src/executor.cpp
    src/metrics.cpp
    src/binance_client.cpp
)

# Create Executable - CSV version
add_executable(hypertradex ${SOURCES})

# Link CURL (AFTER creating the target)
target_link_libraries(hypertradex PUBLIC ${CURL_LIBRARIES})
target_include_directories(hypertradex PUBLIC ${CURL_INCLUDE_DIRS})

# Create Executable - API version
set(SOURCES_API
    src/main_api.cpp
    src/data_loader.cpp
    src/parser.cpp
    src/replay_engine.cpp
    src/strategy.cpp
    src/executor.cpp
    src/metrics.cpp
    src/binance_client.cpp
)

add_executable(hypertradex_api ${SOURCES_API})

# Link CURL for API executable
target_link_libraries(hypertradex_api PUBLIC ${CURL_LIBRARIES})
target_include_directories(hypertradex_api PUBLIC ${CURL_INCLUDE_DIRS})

# # Create Debug executable - Raw API data viewer
# set(SOURCES_DEBUG
#     src/debug_api.cpp
#     src/binance_client.cpp
# )

# add_executable(debug_api ${SOURCES_DEBUG})

# Link CURL for debug executable
# target_link_libraries(debug_api PUBLIC ${CURL_LIBRARIES})
# target_include_directories(debug_api PUBLIC ${CURL_INCLUDE_DIRS})