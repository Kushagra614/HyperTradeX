# 📈 AlgoTradingBot

**AlgoTradingBot** is a **high-performance algorithmic trading system** designed for **low-latency backtesting** using historical market data. Built with **pure C++17** for maximum speed and efficiency, it delivers microsecond-level performance suitable for high-frequency trading applications.

---

## 🚀 Features

* **⚡ High-Performance Engine**
  * **Pure C++17** implementation for maximum speed
  * **Microsecond-level** execution times
  * **Zero runtime Python dependencies** for production use
  * Direct file I/O with optimized JSON parsing

* **📊 Data Management**
  * Historical data via [Yahoo Finance](https://finance.yahoo.com) (setup phase)
  * **Direct C++ file loading** for backtesting (runtime)
  * Efficient in-memory data structures

* **📐 Technical Indicators**
  Built-in support for multiple widely-used indicators:
  * **SMA** – Simple Moving Average
  * **EMA** – Exponential Moving Average
  * **RSI** – Relative Strength Index
  * **MACD** – Moving Average Convergence Divergence

* **🧪 Ultra-Fast Backtesting Engine**
  * **Microsecond-level execution** for real-time performance
  * Simulates trade signals and strategy performance over historical data
  * **Low-latency execution** suitable for HFT applications

* **📈 Comprehensive Performance Analysis**
  Generates detailed reports with:
  * Total Return & Annualized Return
  * Sharpe Ratio
  * Maximum Drawdown
  * Win Rate & Profit Factor
  * Trade-by-trade analysis

---

## ⚙️ Prerequisites

### Runtime Requirements
* GCC/G++ with **C++17** support
* **Make** utility
* **libcurl** development libraries

### Setup Requirements (Data Fetching Only)
* **Python** 3.6+ (for initial data download only)
* **yfinance**, **pandas**, **numpy** (setup phase only)

---

## 📥 Installation

1. **Clone the repository**

   ```bash
   git clone https://github.com/Kushagra614/AlgoTradingBot.git
   cd AlgoTradingBot
   ```

2. **Install system dependencies**

   ```bash
   # Ubuntu/Debian
   sudo apt update
   sudo apt install -y build-essential libcurl4-openssl-dev nlohmann-json3-dev

   # macOS
   brew install curl nlohmann-json
   ```

3. **Build the high-performance C++ engine**

   ```bash
   make clean && make
   ```

4. **Optional: Set up Python environment for data fetching**

   *Only needed if you want to fetch new historical data*

   ```bash
   python3 -m venv venv
   source venv/bin/activate      # Windows: venv\Scripts\activate
   pip install yfinance pandas numpy
   ```

---

## ▶️ Usage


### 🚀 Quick Start (High-Performance Mode)

**Important:** Before running any backtesting command, you must first fetch historical market data using the Yahoo Finance API.
Use the provided Python script to download the required data:

```bash
python3 src/fetch_yahoo.py [SYMBOL] [PERIOD]  # e.g., python3 src/fetch_yahoo.py AAPL 1y
```

The data will be saved in the `data/` directory. After fetching the data, you can run backtests directly with the compiled binary:

```bash
./bin/test_backtest [SYMBOL] [PERIOD]
```

### 🧾 Examples

```bash
./bin/test_backtest AAPL 1y      # Backtest Apple stock for 1 year
./bin/test_backtest GOOGL 3y     # Backtest Google stock for 3 years
./bin/test_backtest MSFT 2y      # Backtest Microsoft stock for 2 years
```

### 📊 Alternative: Using the atb alias (if configured)

```bash
atb AAPL 1y      # Backtest Apple stock for 1 year
atb GOOGL 3y     # Backtest Google stock for 3 years
```

### 📆 Supported Periods

* `1mo` — 1 Month
* `3mo` — 3 Months
* `6mo` — 6 Months
* `1y`  — 1 Year
* `2y`  — 2 Years
* `5y`  — 5 Years

---

## 📊 Trading Strategy

Current implementation uses a combined approach:

* **SMA Crossover**: 10-day vs 20-day
* **RSI Filter**: 14-day, overbought/sold levels at 70/30
* **MACD Confirmation**: Validates signal direction

---

## 📉 Performance Metrics

The system outputs key trading metrics, including:

* ✅ Total Return
* 📆 Annualized Return
* ⚖️ Sharpe Ratio
* 📉 Maximum Drawdown
* 🟩 Win Rate
* 📈 Profit Factor
* 📊 Average Win / Loss
* 🏆 Largest Win / Loss

---

## 🏗️ Architecture

### � Performance Optimizations

* **Pure C++ Runtime**: Zero Python dependencies during backtesting
* **Direct File I/O**: Optimized data loading with no subprocess overhead
* **Optimized Memory Management**: Efficient data structures for large datasets
* **Low-Latency Design**: Microsecond-level execution suitable for HFT

### 📚 Dependencies

#### Runtime Dependencies (C++)
* **Standard Library** (C++17)
* **nlohmann/json** - Fast JSON parsing
* **libcurl** - HTTP client library

#### Setup Dependencies (Python - Optional)
* **yfinance** - Historical data fetching
* **pandas** - Data manipulation
* **numpy** - Numerical computations

> **Note**: Python is only required for initial data fetching. The backtesting engine runs entirely in C++ for maximum performance.

---

## ⚡ Performance Specifications

### 🚀 High-Performance Metrics

| Metric | Specification | Capability |
|--------|---------------|------------|
| **Execution Time** | ~50-100μs | **Microsecond-level** |
| **Memory Usage** | Optimized C++ | **Low footprint** |
| **Dependencies** | C++ only | **Zero runtime deps** |
| **Latency** | Sub-millisecond | **HFT-ready** |

### 📊 Real-World Performance

```bash
# Example: AAPL 1-year backtest
Execution time: 0.08ms
Memory usage: <50MB
Processing: 250+ data points
Result: Production-ready speed
```

**Ideal for:**
- High-Frequency Trading (HFT) applications
- Real-time strategy evaluation
- Large-scale backtesting operations
- Production trading systems

---

## 🤝 Contributing

We welcome contributions!

1. Fork the repository
2. Create your feature branch

   ```bash
   git checkout -b feature/AmazingFeature
   ```
3. Commit your changes

   ```bash
   git commit -m 'Add some AmazingFeature'
   ```
4. Push to your branch

   ```bash
   git push origin feature/AmazingFeature
   ```
5. Open a Pull Request

---


⭐️ **If you found this project useful, consider giving it a star on GitHub!**

---

