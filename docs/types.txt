TEACHING: The Kline Struct
What is a Kline struct?
It represents ONE candlestick bar. Think of it as a snapshot:

What fields does it need?
timestamp_ms (uint64_t) - When did this bar happen? (milliseconds since epoch)
symbol_id (uint32_t) - Which cryptocurrency? (0=BTCUSDT, 1=ETHUSDT, etc)
open (double) - Opening price
high (double) - Highest price
low (double) - Lowest price
close (double) - Closing price
volume (double) - Total volume traded
Why is field order important?
Remember I mentioned cache lines? CPU fetches 64 bytes at a time.

Better order (for cache):

So: timestamp_ms (8) + symbol_id (4) + open/high/low/close/volume (40) = 64 bytes = ONE cache line

TEACHING: The Trade Struct
What is a Trade?
One completed trade = entry + exit

What fields?
trade_id (uint64_t) - Unique identifier
entry_time_ms (uint64_t) - When we entered
exit_time_ms (uint64_t) - When we exited
entry_price (double) - Entry price
exit_price (double) - Exit price
quantity (double) - Amount traded
pnl (double) - Profit/Loss
TEACHING: The Statistics Struct
What is Statistics?
Summary of entire backtest results.

What fields?
total_trades (uint64_t) - How many trades total
total_pnl (double) - Total profit/loss
winning_trades (uint64_t) - Trades that made money
win_rate (double) - % of winning trades (0.0 to 1.0)
max_drawdown (double) - Worst peak-to-trough loss
largest_win (double) - Biggest winning trade
largest_loss (double) - Biggest losing trade