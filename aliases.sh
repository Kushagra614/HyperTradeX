# AlgoTradingBot Command Aliases
alias atb='./bin/test_backtest'              # Shortcut for running backtests
alias yfetch='python3 src/fetch_yahoo.py'    # Shortcut for fetching data
alias atbbuild='make clean && make'           # Shortcut for rebuilding
alias atbclean='rm -rf performance_reports/' # Shortcut for cleaning reports

# Python environment shortcuts
alias atbenv-create='python3 -m venv venv && source venv/bin/activate && pip install yfinance pandas numpy'  # Create and setup Python env
alias atbenv='source venv/bin/activate'        # Activate existing Python env
alias atbenv-deact='deactivate'               # Deactivate Python env

# Examples of usage:
# atb AAPL 1y        (instead of ./bin/test_backtest AAPL 1y)
# yfetch AAPL 1y    (instead of python3 src/fetch_yahoo.py AAPL 1y)
# atbuild           (instead of make clean && make)
# atclean           (instead of rm -rf performance_reports/ && mkdir performance_reports/)
