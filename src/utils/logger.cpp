#include <spdlog/spdlog.h>  // Include spdlog header for logging functionality
#include <spdlog/sinks/stdout_color_sinks.h>  // Include spdlog color sink for colored logging

using namespace spdlog;

void initialize_logger() {
    
    // Create a colored stdout logger (console)
    auto console = stdout_color_mt("console");

    // Set the default log level to debug
    console->set_level(level::debug);

    //set the default logger to the console logger
    set_default_logger(console);

}

//function to log eg msgs
void log_example()
{

    //log diff types of msgs
    info("Deribit Trading System started!");  // Informational message
    warn("This is a warning message.");   // Warning message
    error("This is an error message.");   // Error message

}

