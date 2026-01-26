#pragma once

#include <vector>
#include <string>
// using namespace std;

class DataLoader {
public:
    static std::vector<std::string> load_file(const std::string& filename);
};