#include "parser.h"
#include <sstream>
#include <stdexcept>
using namespace std;

// Initialized a static member
unordered_map<string, uint32_t> Parser::symbol_cache;

Kline Parser::parse_kline(const string& line) {
    stringstream ss(line);
    string field;
    
    // Parse timestamp_ms
    getline(ss, field, ',');
    uint64_t timestamp_ms = stoull(field);

    // Parse symbol
    getline(ss, field, ',');
    uint32_t symbol_id = symbol_to_id(field);

    //parse open
    getline(ss, field, ',');
    double open = stof(field);

    // Parse high
    getline(ss, field, ',');
    double high = stod(field);
    
    // Parse low
    getline(ss, field, ',');
    double low = stod(field);
    
    // Parse close
    getline(ss, field, ',');
    double close = stod(field);
    
    // Parse volume
    getline(ss, field, ',');
    double volume = stod(field);
    
    // Create and return Kline
    return Kline{timestamp_ms, symbol_id, open, high, low, close, volume};

}

uint32_t Parser::symbol_to_id(const string& symbol)
{
    //check cache first
    auto it = symbol_cache.find(symbol);
    if (it != symbol_cache.end()) {
        return it->second;
    }

    //new symbol -> assign next ID
    uint32_t new_id = symbol_cache.size();
    symbol_cache[symbol] = new_id;
    return new_id;  

}