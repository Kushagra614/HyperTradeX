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
        
        # Print only the JSON data to stdout
        print(json.dumps(output), flush=True)
        
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