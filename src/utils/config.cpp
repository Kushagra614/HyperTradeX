#include "config.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Config::Config(const std::string& config_file) {
    std::ifstream file(config_file);
    if (!file.is_open()) {
        std::cerr << "Error opening config file." << std::endl;
        return;
    }

    json j;
    file >> j;

    // Load values from JSON
    api_key = j["api_key"];
    api_secret = j["api_secret"];
    base_url = j["base_url"];
}

std::string Config::getApiKey() const {
    return api_key;
}

std::string Config::getApiSecret() const {
    return api_secret;
}

std::string Config::getBaseUrl() const {
    return base_url;
}
