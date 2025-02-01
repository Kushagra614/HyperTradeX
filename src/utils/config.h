#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {
public:
    Config(const std::string& config_file);  // Constructor to load configuration from a file
    std::string getApiKey() const;          // Getter for API key
    std::string getApiSecret() const;       // Getter for API secret
    std::string getBaseUrl() const;         // Getter for base URL

private:
    std::string api_key;
    std::string api_secret;
    std::string base_url;
};

#endif  // CONFIG_H
