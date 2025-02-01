#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    void log(const std::string& message);  // Function to log messages to a file
};

extern Logger logger;  // Declare a global logger instance

#endif  // LOGGER_H
