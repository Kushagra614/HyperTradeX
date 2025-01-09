# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(DERIBIT_TRADING_SYSTEM VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include project directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files for the project
set(SOURCES
    src/main.cpp
    src/rest_api/order_manager.cpp
    src/rest_api/rest_client.cpp
    src/websocket/websocket_client.cpp
    src/utils/logger.cpp
    src/models/order_book.cpp
    src/config/config.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set output directory for the built binary
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)


# Include uWebSockets headers
include_directories(
    /mnt/d/ME/Work/Codeverse/Coding/C++/Dependencies/uWebSockets/src
    /mnt/d/ME/Work/Codeverse/Coding/C++/Dependencies/uWebSockets/uSockets/src
)

# Add uWebSockets object files
file(GLOB UWS_OBJECT_FILES
    /mnt/d/ME/Work/Codeverse/Coding/C++/Dependencies/uWebSockets/uSockets/*.o
)

# Link uWebSockets object files to the target
target_sources(${PROJECT_NAME} PRIVATE ${UWS_OBJECT_FILES})

# Additional compile definitions for uWebSockets
target_compile_definitions(${PROJECT_NAME} PRIVATE LIBUS_USE_LIBUV=0)

# Add Boost dependency (adjust versions if needed)
find_package(Boost 1.71 REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)
endif()

# Add spdlog dependency
find_package(spdlog REQUIRED)
if(spdlog_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
endif()

# Include debugging and optimization flags (optional)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
