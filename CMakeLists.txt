cmake_minimum_required(VERSION 3.10)

project(HyperTradeX)

set(CMAKE_CXX_STANDARD 17)

# Add source files
add_executable(HyperTradeX
    src/main.cpp
    src/binance/binance_api.cpp
    src/binance/binance_ws_client.cpp
    src/websocket/websocket_server.cpp
    src/models/orderbook.cpp
    src/utils/logger.cpp
    src/utils/config.cpp
)

# Link necessary libraries
# Example: find_package(spdlog REQUIRED)
# target_link_libraries(HyperTradeX spdlog::spdlog)
