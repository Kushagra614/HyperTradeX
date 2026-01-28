# HyperTradeX - Backtesting Engine

A modern C++17 cryptocurrency backtesting system for learning systems engineering and building trading infrastructure.

## 📋 Overview

HyperTradeX demonstrates practical concepts:
- **Data pipeline** - Load, parse, and replay market data
- **Trading strategy** - Buy/sell logic with state management
- **Execution simulator** - Realistic order fills and PnL calculation
- **Performance metrics** - Win rate, drawdown, latency tracking
- **REST API integration** - Real Binance market data
- **Modern C++** - C++17, efficient memory usage, RAII patterns

## 🎯 Features

- **Data Loader** - CSV file reading with buffering
- **Parser** - CSV to Kline conversion
- **Replay Engine** - Candlestick playback
- **Strategy** - Trading logic with state machine
- **Executor** - Order execution and fill simulation
- **Metrics** - PnL tracking, win rate, drawdown, latency percentiles
- **Binance API Client** - Real-time market data integration
- **JSON Parsing** - JSON response handling

##  Getting Started

### Prerequisites
- **OS**: Linux/Mac
- **Compiler**: g++ with C++17 support
- **Build System**: CMake 3.16+
- **Libraries**: 
  - libcurl 8.5.0+ (HTTP client)
  - nlohmann/json 3.11.3+ (JSON parsing)

### Installation

```bash
# Clone repository
git clone https://github.com/Kushagra614/AlgoTradingBot.git
cd HyperTradeX

# Install dependencies (Ubuntu/Debian)
sudo apt-get install -y libcurl4-openssl-dev nlohmann-json3-dev

# Build project
mkdir build && cd build
cmake ..
make

# Run backtest
./hypertradex
```

### Quick Start

**CSV Backtest** (Synthetic data):
```bash
# Uses sample_ticks.csv (included)
./hypertradex
```

**Live Backtest** (Real Binance data - coming soon):
```cpp
// In main.cpp:
BinanceClient binance;
auto klines = binance.fetch_klines("BTCUSDT", "1m", 100);
// Run backtest on real data
```

## 📊 Example Output

```
Backtest Results
================
Total Trades: 10
Winning Trades: 10 (100.0%)
Total PnL: $520.00
Largest Win: $65.00
Largest Loss: $0.00
Max Drawdown: 0.0%

Latency Metrics
===============
Avg Entry Latency: 0.00 μs
Avg Exit Latency: 0.00 μs
P99 Latency: 0.00 μs
```

## 🛠️ Development Guide

### Adding a New Component

1. Create `src/mycomponent.h` (interface)
2. Create `src/mycomponent.cpp` (implementation)
3. Add to `CMakeLists.txt`:
   ```cmake
   set(SOURCES
       ...
       src/mycomponent.cpp
   )
   ```
4. Compile and test

### Testing

Run the existing backtest:
```bash
cd build
./hypertradex
```

### Build Configuration

**Debug** (with symbols):
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

**Release** (optimized):
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## 📁 Project Structure

```
HyperTradeX/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── src/
│   ├── main.cpp               # Entry point
│   ├── types.h                # Data structures
│   ├── data_loader.h/.cpp     # CSV file reading
│   ├── parser.h/.cpp          # CSV→Kline parsing
│   ├── replay_engine.h/.cpp   # Playback engine
│   ├── strategy.h/.cpp        # Trading logic
│   ├── executor.h/.cpp        # Order execution
│   ├── metrics.h/.cpp         # Statistics calculation
│   └── binance_client.h/.cpp  # Binance REST API
├── data/
│   └── sample_ticks.csv       # Sample market data
└── build/                     # Compiled binaries
```

## 🔗 API Reference

### BinanceClient

```cpp
BinanceClient client("https://api.binance.com");

// Fetch klines (candlesticks)
vector<Kline> klines = client.fetch_klines(
    "BTCUSDT",    // Symbol
    "1m",         // Interval: 1m, 5m, 15m, 1h, etc
    100           // Limit: 1-1000 candles
);
```

### Strategy

```cpp
Strategy strategy;

// Process each candle
for (const auto& kline : klines) {
    auto trade = strategy.on_kline(kline);
    if (trade) {
        // Trade triggered
        executor.execute(*trade);
    }
}
```

### Metrics

```cpp
Metrics metrics;

// Compute statistics
auto stats = metrics.calculate(trades);
std::cout << "Win Rate: " << stats.win_rate * 100 << "%\n";
std::cout << "Total PnL: $" << stats.total_pnl << "\n";
std::cout << "P99 Latency: " << stats.p99_latency_us << " μs\n";
```

## 📚 Learning Resources

### Concepts Covered

1. **File I/O & Buffering** - Why buffers improve performance
2. **CSV Parsing** - Efficient string handling, symbol interning
3. **State Machines** - Clean strategy logic with states
4. **Callbacks** - Replay engine uses functional programming
5. **HTTP & APIs** - REST client, error handling, rate limiting
6. **JSON Parsing** - Modern C++ JSON libraries
7. **Performance Metrics** - Win rate, drawdown, latency percentiles
8. **Memory Safety** - RAII, std::vector, std::optional
9. **CMake** - Professional build system

### References

- **Binance API Docs**: https://docs.binance.us/
- **libcurl Manual**: https://curl.se/libcurl/c/
- **nlohmann/json Docs**: https://json.nlohmann.me/
- **C++17 Standard**: https://en.cppreference.com/

## 🎓 Educational Purpose

This project is designed for learning, not production trading. Use it to:
- Understand **how backtesting engines work**
- Learn **systems engineering principles**
- Practice **modern C++**
- Build **data processing pipelines**
- Integrate **third-party APIs**

## ⚠️ Disclaimers

- **Not for real trading** - Backtests on synthetic or historical data don't guarantee future results
- **Educational only** - Designed for learning, not production use
- **Crypto markets** - Highly volatile; past performance ≠ future results
- **No financial advice** - This is purely educational code

## 🤝 Contributing

This is a personal learning project, but suggestions are welcome!

## 📝 License

Educational - Use freely for learning purposes.

## 👤 Author

Kushagra Vardhan  
Learning systems engineering through building real infrastructure.

---

**Last Updated**: January 28, 2026  
**Current Phase**: Phase 2 (Binance API Integration)  
**Status**: Active Development
