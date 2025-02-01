#include "logger.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

void Logger::log(const std::string& message) {
    std::ofstream log_file("hypertradex.log", std::ios::app);
    if (log_file.is_open()) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        log_file << std::ctime(&now) << " - " << message << std::endl;
    }
}

Logger logger; // Create a global logger instance
