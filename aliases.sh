# AlgoTradingBot Command Aliases
alias atb='./bin/test_backtest'              # Shortcut for running backtests
alias yfetch='python3 scripts/fetch_data.py'  # Shortcut for fetching data
alias atbbuild='make clean && make'           # Shortcut for rebuilding
alias atbclean='make clean_reports'           # Shortcut for cleaning reports

# Python environment shortcuts
alias atbenv-create='python3 -m venv venv && source venv/bin/activate && pip install yfinance pandas numpy'  # Create and setup Python env
alias atbenv='source venv/bin/activate'        # Activate existing Python env
alias atbenv-deact='deactivate'               # Deactivate Python env

# Examples of usage:
# atb AAPL 1y        (instead of ./bin/test_backtest AAPL 1y)
# yfetch AAPL 1y    (instead of python3 scripts/fetch_data.py AAPL 1y)
# atbbuild          (instead of make clean && make)
# atbclean          (instead of rm -rf performance_reports/)

# cat aliases.sh >> ~/.bashrc   --> cmd for adding aliases file to bashrc
# source ~/.bashrc  --> reload your bashrc

# Advanced aliases for power users
alias atbtest='atbbuild && atb'                    # Build and test in one command
alias atbquick='echo "1" | atb'                   # Quick test with SMA strategy
alias atbbest='echo "5" | atb'                    # Quick test with best performer
alias atbstats='ls -la data/ && echo "Available datasets:"' # Show available data
alias atblogs='ls -la performance_reports/ 2>/dev/null || echo "No reports yet"' # Show reports

# Multi-stock testing
alias atbcompare='python3 scripts/compare_stocks.py'           # Enhanced stock comparison with metrics table
alias atbcompare-simple='function _atbcompare() { echo "Testing $1 vs $2 on $3 period:"; echo "=== $1 ==="; echo "1" | atb $1 $3; echo "=== $2 ==="; echo "1" | atb $2 $3; }; _atbcompare' # Simple side-by-side comparison

# Data management
alias atbfetch-major='yfetch AAPL 1y && yfetch GOOGL 1y && yfetch MSFT 1y && yfetch TSLA 1y && echo "Major stocks data updated!"' # Fetch major stocks
alias atbfetch-crypto='yfetch BTC-USD 1y && yfetch ETH-USD 1y && echo "Crypto data updated!"' # Fetch crypto data

# Examples of advanced usage:
# atbtest AAPL 1y       --> Build project and run AAPL backtest
# atbquick TSLA 2y      --> Quick SMA test on Tesla (no menu prompt)
# atbbest GOOGL 1y      --> Quick best performer test on Google
# atbstats              --> Show all available data files
# atblogs               --> Check if any performance reports exist
# atbcompare AAPL TSLA 1y --> Enhanced comparison with metrics table
# atbcompare AAPL GOOGL MSFT 1y --> Compare 3+ stocks with best performer
# atbcompare-simple AAPL TSLA 1y --> Simple side-by-side comparison
# atbfetch-major        --> Download data for AAPL, GOOGL, MSFT, TSLA
# atbfetch-crypto       --> Download Bitcoin and Ethereum data