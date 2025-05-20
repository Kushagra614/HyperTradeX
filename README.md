# AlgoTradingBot

A powerful algorithmic trading bot for backtesting trading strategies using historical market data. This project combines the efficiency of C++ with Python's data fetching capabilities to create a robust trading system.

## Features

- **Data Fetching**: Real-time historical data from Yahoo Finance
- **Technical Analysis**: Multiple indicators including:
  - Moving Averages (SMA, EMA)
  - RSI (Relative Strength Index)
  - MACD (Moving Average Convergence Divergence)
- **Backtesting Engine**: Simulate trading strategies with detailed performance metrics
- **Performance Analysis**: Comprehensive reporting including:
  - Total and Annualized Returns
  - Sharpe Ratio
  - Maximum Drawdown
  - Win Rate and Profit Factor

## Prerequisites

- C++17 or higher
- Python 3.6 or higher
- Make
- GCC/G++ compiler

## Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/AlgoTradingBot.git
cd AlgoTradingBot
```

2. Set up Python virtual environment and install dependencies:
```bash
python3 -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate
pip install yfinance pandas numpy
```

3. Build the project:
```bash
make clean && make
```

## Usage

Run a backtest using the provided alias:
```bash
atb [symbol] [period]
```

### Examples:
```bash
atb AAPL 1y    # Test Apple stock for 1 year
atb GOOGL 3y   # Test Google stock for 3 years
```

### Valid Periods:
- 1mo (1 month)
- 3mo (3 months)
- 6mo (6 months)
- 1y (1 year)
- 2y (2 years)
- 5y (5 years)


## Trading Strategy

The current implementation includes an enhanced strategy with:
- Moving Average Crossover (10 and 20-day periods)
- RSI Filter (14-day period, 30/70 levels)
- MACD Confirmation

## Performance Metrics

The system calculates various performance metrics:
- Total Return
- Annualized Return
- Sharpe Ratio
- Maximum Drawdown
- Win Rate
- Profit Factor
- Average Win/Loss
- Largest Win/Loss

## Dependencies

### C++ Libraries
- Standard Library (C++17)
- nlohmann/json
- Boost

### Python Libraries
- yfinance
- pandas
- numpy

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Yahoo Finance for providing market data
- All contributors who have helped improve this project

⭐️ If you like this project, please give it a star on GitHub! 