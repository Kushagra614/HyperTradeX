# Parser Implementation - Complete Teaching

## TEACHING: What is a Parser?

### The Problem

We have CSV lines like this:
```
1704067200000,BTCUSDT,42500.00,42650.00,42400.00,42550.00,1234.56
```

We need to convert it to a `Kline` struct:
```cpp
Kline {
    timestamp_ms: 1704067200000,
    symbol_id: 0,
    open: 42500.00,
    high: 42650.00,
    low: 42400.00,
    close: 42550.00,
    volume: 1234.56
}
```

**The parser does this conversion.**

---

## TEACHING: How Does Parsing Work?

### Step 1: Split by Comma

CSV = "Comma Separated Values"

```
"1704067200000,BTCUSDT,42500.00,42650.00,42400.00,42550.00,1234.57"
         ↓
     Split by ','
         ↓
["1704067200000", "BTCUSDT", "42500.00", "42650.00", "42400.00", "42550.00", "1234.56"]
```

### Step 2: Convert Each Field

```
Index 0: "1704067200000"  → uint64_t timestamp_ms
Index 1: "BTCUSDT"         → uint32_t symbol_id (map to ID)
Index 2: "42500.00"        → double open
Index 3: "42650.00"        → double high
Index 4: "42400.00"        → double low
Index 5: "42550.00"        → double close
Index 6: "1234.56"         → double volume
```

### Step 3: Create Kline

```cpp
Kline kline;
kline.timestamp_ms = 1704067200000;
kline.symbol_id = 0;
kline.open = 42500.00;
// ... etc
return kline;
```

---

## TEACHING: How to Parse a CSV Line?

### Option 1: Using `std::stringstream` (Simple & Recommended for Phase 1)

```cpp
string line = "1704067200000,BTCUSDT,42500.00,42650.00,42400.00,42550.00,1234.56";
stringstream ss(line);
string field;

// Read first field (timestamp)
getline(ss, field, ',');  // Reads until comma
uint64_t timestamp_ms = stoull(field);  // string to unsigned long long

// Read second field (symbol)
getline(ss, field, ',');
uint32_t symbol_id = symbol_to_id(field);

// Read third field (open)
getline(ss, field, ',');
double open = stod(field);  // string to double

// Read fourth field (high)
getline(ss, field, ',');
double high = stod(field);

// Read fifth field (low)
getline(ss, field, ',');
double low = stod(field);

// Read sixth field (close)
getline(ss, field, ',');
double close = stod(field);

// Read seventh field (volume)
getline(ss, field, ',');
double volume = stod(field);
```

**Functions to know:**
- `stringstream ss(line)` = create stream from string
- `getline(ss, field, ',')` = read until comma delimiter
- `stoull(field)` = string to unsigned long long (uint64_t)
- `stod(field)` = string to double

### Why This Approach?

✅ Simple to understand  
✅ Works well for CSV  
✅ Easy to debug  
✅ Good for Phase 1 learning  
✅ Standard C++ library (no dependencies)  

### Performance Note

For Phase 1, `stringstream` is fine. In Phase 4 optimization, we might switch to:
- Manual parsing (skip allocations)
- SIMD parsing (process multiple fields at once)
- But we learn with stringstream first!

---

## TEACHING: Symbol Mapping (Caching)

### Problem

We read "BTCUSDT" but we want `symbol_id = 0`, "ETHUSDT" = 1, etc.

We can't allocate new strings every time (slow). We need to cache.

### Solution: Static UnorderedMap Cache

```cpp
// Static map: stores symbol name → ID
static unordered_map<string, uint32_t> symbol_cache;

uint32_t Parser::symbol_to_id(const string& symbol) {
    // Check if we've seen this symbol before
    auto it = symbol_cache.find(symbol);
    if (it != symbol_cache.end()) {
        return it->second;  // Found! Return cached ID
    }
    
    // New symbol: assign next ID
    uint32_t new_id = symbol_cache.size();
    symbol_cache[symbol] = new_id;
    return new_id;
}
```

### Why Caching?

**Without cache (BAD):**
```cpp
if (symbol == "BTCUSDT") return 0;
else if (symbol == "ETHUSDT") return 1;
else if (symbol == "BNBUSDT") return 2;
// ... string compares are slow!
```

**With cache (GOOD):**
```cpp
// First time: "BTCUSDT" → O(hash) lookup → assign ID 0, cache it
// Second time: "BTCUSDT" → O(hash) lookup → return cached ID 0
// Hash lookup is O(1) average case, much faster than string compare
```

### How UnorderedMap Works

| Operation | Time | Why |
|-----------|------|-----|
| Insert | O(1) average | Hash function → bucket |
| Find | O(1) average | Hash function → bucket |
| Find (worst) | O(n) | Hash collision chain |

**For our use case:** We have ~10 symbols max, so O(1) is guaranteed.

---

## parser.h Header File

```cpp
#pragma once

#include <string>
#include <unordered_map>
#include "types.h"

using namespace std;

class Parser {
public:
    static Kline parse_kline(const string& line);
    static uint32_t symbol_to_id(const string& symbol);

private:
    static unordered_map<string, uint32_t> symbol_cache;
};
```

**Key Points:**
- `static` functions = class-level (no instance needed)
- `symbol_cache` = private (only Parser uses it)
- `static unordered_map` = shared across all calls

---

## parser.cpp Implementation

```cpp
#include "parser.h"
#include <sstream>
#include <stdexcept>

using namespace std;

// Initialize static member (must happen in .cpp, not .h)
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
    
    // Parse open
    getline(ss, field, ',');
    double open = stod(field);
    
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

uint32_t Parser::symbol_to_id(const string& symbol) {
    // Check cache first
    auto it = symbol_cache.find(symbol);
    if (it != symbol_cache.end()) {
        return it->second;
    }
    
    // New symbol: assign next ID
    uint32_t new_id = symbol_cache.size();
    symbol_cache[symbol] = new_id;
    return new_id;
}
```

**Important:** Static member initialization at top of .cpp file!

---

## Key Concepts

### String Conversion Functions

| Function | Input | Output | Use Case |
|----------|-------|--------|----------|
| `stoull()` | "1704067200000" | uint64_t | Large integers, timestamps |
| `stoi()` | "123" | int | Small integers |
| `stod()` | "42500.00" | double | Floating point, prices |
| `stof()` | "42500.00" | float | Smaller floating point |

### StringStream Delimiters

```cpp
// Read until space
getline(ss, field, ' ');

// Read until comma (CSV)
getline(ss, field, ',');

// Read until newline (default)
getline(ss, field);
```

### Unordered Map Lookup

```cpp
auto it = map.find(key);
if (it != map.end()) {
    // Key exists, use it->second
    return it->second;
} else {
    // Key doesn't exist
}
```

---

## Performance Impact

### Without Symbol Cache (BAD)
```
1M lines × string comparison = slow
Each "BTCUSDT" requires string compare O(n)
Total: 1M × O(n) where n = string length
```

### With Symbol Cache (GOOD)
```
First "BTCUSDT": hash lookup, store ID 0
Remaining 999,999 "BTCUSDT": hash lookup O(1) = return 0
Total: 1 × O(n) + 999,999 × O(1) = much faster!
```

**Speedup:** 1000x for repeated symbols!

---

## Why This Matters

**For Phase 1:**
1. Learn CSV parsing fundamentals
2. Understand caching benefit
3. Implement simple, readable code

**For Phase 4 (optimization):**
1. Switch to manual parsing (skip allocations)
2. Use SIMD to parse multiple fields at once
3. Pre-allocate symbol IDs (no dynamic caching)

---

## Next Steps

Once parsing works:
1. ✅ Load CSV lines (data_loader)
2. ✅ Parse to Kline structs (parser)
3. ⏳ Replay in order (replay_engine)
4. ⏳ Strategy makes decisions
5. ⏳ Execution fills orders
6. ⏳ Metrics tracks performance

