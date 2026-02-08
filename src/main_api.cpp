#include <iostream>
#include <iomanip>
#include <vector>
#include "binance_client.h"
#include "replay_engine.h"
#include "strategy.h"
#include "executor.h"
#include "metrics.h"

using namespace std;

int main() {
    try {
        cout << "=== HyperTradeX Phase 2 - Real API Data Backtest ===" << endl;
        
        // Step 1: Fetch klines from Binance API
        cout << "\n[1] Fetching klines from Binance API..." << endl;
        BinanceClient client("https://api.binance.com");
        
        // Fetch 100 candles of 1-minute data for BTCUSDT
        vector<Kline> klines = client.fetch_klines("BTCUSDT", "1m", 100);
        cout << "Fetched " << klines.size() << " klines from Binance API" << endl;
        
        if (klines.empty()) {
            cerr << "ERROR: No klines fetched from API!" << endl;
            return 1;
        }
        
        // Print first and last kline for verification
        cout << "  First kline timestamp: " << klines[0].timestamp_ms << " ms" << endl;
        cout << "  Last kline timestamp: " << klines.back().timestamp_ms << " ms" << endl;
        cout << "  First kline close price: $" << fixed << setprecision(2) << klines[0].close << endl;
        cout << "  Last kline close price: $" << klines.back().close << endl;
        
        // Step 2: Create backtest components
        cout << "\n[2] Creating backtest components..." << endl;
        const uint64_t initial_capital = 1000000;  // 1M capital
        const uint64_t hold_duration_ms = 5000;    // Hold 5 seconds
        
        Strategy strategy(hold_duration_ms);
        Executor executor(initial_capital);
        Metrics metrics(initial_capital);
        vector<Trade> trades;
        
        ReplayEngine engine(klines);
        
        // Step 3: Run backtest
        cout << "\n[3] Running backtest on API data..." << endl;
        engine.replay([&](const Kline& kline) {
            // Strategy decides
            auto decision = strategy.on_kline(kline);
            
            // Executor executes
            auto result = executor.on_kline(kline, decision);
            
            // If trade closed, record it
            if (result.has_value()) {
                trades.push_back(result.value());
            }
        });
        
        cout << "Backtest complete! Closed " << trades.size() << " trades" << endl;
        
        // Step 4: Calculate metrics
        cout << "\n[4] Calculating metrics..." << endl;
        auto stats = metrics.calculate(trades);
        
        // Step 5: Print results
        cout << "\n";
        cout << "==========================================" << endl;
        cout << "     BACKTEST RESULTS (Live API Data)" << endl;
        cout << "==========================================" << endl;
        cout << fixed << setprecision(2);
        cout << left << setw(25) << "Initial Capital:" << "$" << initial_capital << endl;
        cout << left << setw(25) << "Total Trades:" << stats.total_trades << endl;
        cout << left << setw(25) << "Winning Trades:" << stats.winning_trades << endl;
        cout << left << setw(25) << "Win Rate:" << stats.win_rate << "%" << endl;
        cout << left << setw(25) << "Total PnL:" << "$" << stats.total_pnl << endl;
        cout << left << setw(25) << "Max Drawdown:" << "$" << stats.max_drawdown << endl;
        cout << left << setw(25) << "Largest Win:" << "$" << stats.largest_win << endl;
        cout << left << setw(25) << "Largest Loss:" << "$" << stats.largest_loss << endl;
        cout << "-------------------------------------------" << endl;
        cout << left << setw(25) << "Avg Entry Latency:" << stats.avg_entry_latency_us << " μs" << endl;
        cout << left << setw(25) << "Avg Exit Latency:" << stats.avg_exit_latency_us << " μs" << endl;
        cout << left << setw(25) << "P99 Latency:" << stats.p99_latency_us << " μs" << endl;
        cout << left << setw(25) << "P50 Latency:" << stats.p50_latency_us << " μs" << endl;
        cout << "==========================================" << endl;
        
        return 0;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
