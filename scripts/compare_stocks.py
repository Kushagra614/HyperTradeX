#!/usr/bin/env python3
"""
Advanced Stock Comparison Tool for AlgoTradingBot
Compares multiple stocks side-by-side with detailed metrics
"""

import json
import sys
import subprocess
import os
from datetime import datetime

def run_backtest(symbol, period, strategy="1"):
    """Run backtest and capture output"""
    try:
        # Run the backtest with specified strategy
        cmd = f'echo "{strategy}" | ./bin/test_backtest {symbol} {period}'
        result = subprocess.run(cmd, shell=True, capture_output=True, text=True, cwd='.')
        return result.stdout
    except Exception as e:
        return f"Error running backtest for {symbol}: {e}"

def parse_backtest_output(output):
    """Parse backtest output to extract key metrics"""
    metrics = {}
    lines = output.split('\n')

    for line in lines:
        line = line.strip()
        if 'Total Return:' in line:
            metrics['return'] = line.split('Total Return:')[1].strip()
        elif 'Sharpe Ratio:' in line:
            metrics['sharpe'] = line.split('Sharpe Ratio:')[1].strip()
        elif 'Maximum Drawdown:' in line:
            metrics['drawdown'] = line.split('Maximum Drawdown:')[1].strip()
        elif 'Total Trades:' in line:
            metrics['trades'] = line.split('Total Trades:')[1].strip()
        elif 'Win Rate:' in line:
            metrics['win_rate'] = line.split('Win Rate:')[1].strip()
        elif 'Final Capital:' in line:
            metrics['final_capital'] = line.split('Final Capital:')[1].strip()

    return metrics

def compare_stocks(stocks, period, strategy="1"):
    """Compare multiple stocks and display results"""
    print(f"🔥 STOCK COMPARISON REPORT")
    print(f"📅 Period: {period} | 📈 Strategy: SMA Crossover")
    print("=" * 80)
    
    results = {}
    
    # Run backtests for each stock
    for stock in stocks:
        print(f"⏳ Running backtest for {stock}...")
        output = run_backtest(stock, period, strategy)
        # Debug: Print first few lines of output
        if not output.strip():
            print(f"⚠️  No output received for {stock}")
        results[stock] = parse_backtest_output(output)
    
    # Display comparison table
    print(f"\n📊 PERFORMANCE COMPARISON")
    print("-" * 80)
    print(f"{'Stock':<8} {'Return':<10} {'Sharpe':<8} {'Drawdown':<10} {'Trades':<8} {'Win Rate':<10}")
    print("-" * 80)
    
    for stock, metrics in results.items():
        return_val = metrics.get('return', 'N/A')
        sharpe_val = metrics.get('sharpe', 'N/A')
        drawdown_val = metrics.get('drawdown', 'N/A')
        trades_val = metrics.get('trades', 'N/A')
        win_rate_val = metrics.get('win_rate', 'N/A')
        
        print(f"{stock:<8} {return_val:<10} {sharpe_val:<8} {drawdown_val:<10} {trades_val:<8} {win_rate_val:<10}")
    
    # Find best performer
    best_stock = None
    best_return = float('-inf')
    
    for stock, metrics in results.items():
        try:
            return_str = metrics.get('return', '0%').replace('%', '')
            return_val = float(return_str)
            if return_val > best_return:
                best_return = return_val
                best_stock = stock
        except:
            continue
    
    print("-" * 80)
    if best_stock:
        print(f"🏆 BEST PERFORMER: {best_stock} ({best_return:+.2f}%)")
    print(f"📈 Analysis completed at {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 scripts/compare_stocks.py STOCK1 STOCK2 [STOCK3...] PERIOD")
        print("Example: python3 scripts/compare_stocks.py AAPL GOOGL TSLA 1y")
        sys.exit(1)
    
    # Parse arguments
    stocks = sys.argv[1:-1]  # All arguments except the last one
    period = sys.argv[-1]    # Last argument is the period
    
    compare_stocks(stocks, period)
