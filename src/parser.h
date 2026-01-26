#pragma once

#include <string>
#include <unordered_map>
#include "types.h"

using namespace std;

class Parser
{
public:
    static Kline parse_kline(const string &line);
    static uint32_t symbol_to_id(const string &symbol);

private:
    static unordered_map<string, uint32_t> symbol_cache;
};