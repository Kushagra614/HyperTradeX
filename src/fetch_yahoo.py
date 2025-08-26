#!/usr/bin/env python3
import yfinance as yf
import sys
import json
from datetime import datetime
import warnings
import os

# Suppress FutureWarnings and redirect stderr
warnings.filterwarnings('ignore', category=FutureWarning)
stderr = sys.stderr
sys.stderr = open(os.devnull, 'w')

def fetch_stock_data(symbol, period='1mo', interval='1d'):
    try:
        # Validate period
        valid_periods = ['1mo', '3mo', '6mo', '1y', '2y', '5y']
        if period not in valid_periods:
            print(json.dumps({"error": f"Invalid period. Valid periods are: {', '.join(valid_periods)}"}))
            return

        # Download stock data
        data = yf.download(symbol, period=period, interval=interval, progress=False)
        
        # Restore stderr
        sys.stderr = stderr
        
        if data.empty:
            print(json.dumps({"error": f"No data found for {symbol}"}))
            return
        
        # Convert DataFrame to list of dictionaries with proper type conversion
        result = []
        for index, row in data.iterrows():
            # Convert timestamp to string and ensure all values are native Python types
            entry = {
                'date': index.strftime('%Y-%m-%d'),
                'open': float(row['Open'].iloc[0]),
                'high': float(row['High'].iloc[0]),
                'low': float(row['Low'].iloc[0]),
                'close': float(row['Close'].iloc[0]),
                'volume': int(row['Volume'].iloc[0])
            }
            result.append(entry)
        
        # Create the final JSON structure
        output = {
            "symbol": str(symbol),
            "period": str(period),
            "interval": str(interval),
            "data": result
        }
        
        # Ensure data directory exists
        data_dir = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'data')
        os.makedirs(data_dir, exist_ok=True)
        
        # Save to file in data directory
        filename = os.path.join(data_dir, f"{symbol}_{period}.json")
        with open(filename, 'w') as f:
            json.dump(output, f, indent=2)

        # Restore stderr to print save message there
        sys.stderr = stderr
        print(f"Data saved to {filename}", file=sys.stderr, flush=True)

        # Output JSON to stdout for piping
        print(json.dumps(output, indent=2), flush=True)
        
    except Exception as e:
        # Restore stderr before printing error
        sys.stderr = stderr
        print(json.dumps({"error": str(e)}), flush=True)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(json.dumps({"error": "Usage: python3 fetch_yahoo.py <symbol> [period] [interval]"}))
        sys.exit(1)
    
    symbol = sys.argv[1]
    period = sys.argv[2] if len(sys.argv) > 2 else '1mo'
    interval = sys.argv[3] if len(sys.argv) > 3 else '1d'
    
    fetch_stock_data(symbol, period, interval) 