#include <iostream>
#include <iomanip>
#include <vector>
#include "data_loader.h"
#include "parser.h"
#include "replay_engine.h"
#include "strategy.h"
#include "executor.h"
#include "metrics.h"

using namespace std;

int main() {
    try {
        cout << "=== HyperTradeX Phase 1 - End-to-End Backtest ===" << endl;
        
        // Step 1: Load CSV file
        cout << "\n[1] Loading CSV file..." << endl;
        auto lines = DataLoader::load_file("data/BTCUSDT_1m.csv");
        cout << "Loaded " << lines.size() << " lines" << endl;
        
        // Step 2: Parse klines (skip header)
        cout << "\n[2] Parsing klines..." << endl;
        vector<Kline> klines;
        for (size_t i = 1; i < lines.size(); ++i) {
            klines.push_back(Parser::parse_kline(lines[i]));
        }
        cout << "Parsed " << klines.size() << " klines" << endl;
        
        // Step 3: Create backtest components
        cout << "\n[3] Creating backtest components..." << endl;
        const uint64_t initial_capital = 1000000;  // 1M capital
        const uint64_t hold_duration_ms = 5000;    // Hold 5 seconds
        
        Strategy strategy(hold_duration_ms);
        Executor executor(initial_capital);
        Metrics metrics(initial_capital);
        vector<Trade> trades;
        
        ReplayEngine engine(klines);
        
        // Step 4: Run backtest
        cout << "\n[4] Running backtest..." << endl;
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
        
        // Step 5: Calculate metrics
        cout << "\n[5] Calculating metrics..." << endl;
        auto stats = metrics.calculate(trades);
        
        // Step 6: Print results
        cout << "\n";
        cout << "==========================================" << endl;
        cout << "           BACKTEST RESULTS" << endl;
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
        cout << "==========================================" << endl;
        
        return 0;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
