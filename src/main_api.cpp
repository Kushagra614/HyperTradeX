#include <iostream>
#include <iomanip>
#include "binance_client.h"

using namespace std;

int main() {
    try {
        cout << "=== Binance API - Raw Market Data Debug ===" << endl;
        
        cout << "\n[1] Connecting to Binance API..." << endl;
        BinanceClient client("https://api.binance.com");
        
        cout << "[2] Fetching 5 klines from BTCUSDT (1m interval)..." << endl;
        vector<Kline> klines = client.fetch_klines("BTCUSDT", "1m", 100);
        
        cout << "\n[3] Raw Market Data Received:\n" << endl;
        cout << "==========================================" << endl;
        cout << left << setw(12) << "Index"
             << setw(18) << "Timestamp"
             << setw(15) << "Open"
             << setw(15) << "High"
             << setw(15) << "Low"
             << setw(15) << "Close"
             << setw(15) << "Volume" << endl;
        cout << "==========================================" << endl;
        
        for (size_t i = 0; i < klines.size(); ++i) {
            const auto& kline = klines[i];
            cout << left << setw(12) << i
                 << setw(18) << kline.timestamp_ms
                 << fixed << setprecision(2)
                 << setw(15) << kline.open
                 << setw(15) << kline.high
                 << setw(15) << kline.low
                 << setw(15) << kline.close
                 << setw(15) << kline.volume << endl;
        }
        
        cout << "==========================================" << endl;
        cout << "\n✅ Successfully fetched and parsed " << klines.size() << " klines!" << endl;
        
        return 0;
        
    } catch (const exception& e) {
        cerr << "\n❌ Error: " << e.what() << endl;
        return 1;
    }
}
