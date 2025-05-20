# 📈 AlgoTradingBot

**AlgoTradingBot** is a high-performance algorithmic trading system designed to backtest strategies using historical market data. It combines the **speed of C++** with the **flexibility of Python** to deliver robust analysis and performance evaluation.

---

## 🚀 Features

* **📊 Data Fetching**

  * Real-time historical data via [Yahoo Finance](https://finance.yahoo.com)

* **📐 Technical Indicators**
  Built-in support for multiple widely-used indicators:

  * **SMA** – Simple Moving Average
  * **EMA** – Exponential Moving Average
  * **RSI** – Relative Strength Index
  * **MACD** – Moving Average Convergence Divergence

* **🧪 Backtesting Engine**

  * Simulates trade signals and strategy performance over historical data
  * Efficient core logic written in **C++17**

* **📈 Performance Analysis**
  Generates a detailed report with:

  * Total Return & Annualized Return
  * Sharpe Ratio
  * Maximum Drawdown
  * Win Rate
  * Profit Factor

---

## ⚙️ Prerequisites

* GCC/G++ with **C++17** support
* **Python** 3.6 or higher
* **Make** utility

---

## 📥 Installation

1. **Clone the repository**

   ```bash
   git clone https://github.com/yourusername/AlgoTradingBot.git
   cd AlgoTradingBot
   ```

2. **Set up Python environment**

   ```bash
   python3 -m venv venv
   source venv/bin/activate      # Windows: venv\Scripts\activate
   pip install yfinance pandas numpy
   ```

3. **Build the C++ project**

   ```bash
   make clean && make
   ```

---

## ▶️ Usage

Run a backtest using the `atb` alias:

```bash
atb [symbol] [period]
```

### 🧾 Examples

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

## 📚 Dependencies

### C++ Libraries

* Standard Library (C++17)
* `nlohmann/json`
* `Boost`

### Python Libraries

* `yfinance`
* `pandas`
* `numpy`

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

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for more details.

---

## 🙌 Acknowledgments

* **Yahoo Finance** for market data
* All contributors who helped improve the project

---

⭐️ **If you found this project useful, consider giving it a star on GitHub!**

---

