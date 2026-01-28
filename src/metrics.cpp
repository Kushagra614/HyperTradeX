#include "metrics.h"
#include "types.h"
#include <algorithm>
#include <limits>
using namespace std;

Metrics::Metrics(uint64_t initial_capital)
    : initial_capital_(initial_capital) {}

Statistics Metrics::calculate(const vector<Trade>& trades)
{
    //handle the empty trade case
    if( trades.empty())
    {
        return Statistics{0, 0, 0.0, 0.0, 0.0, 0.0, 0.0};
    }

    uint64_t total_trades = trades.size();
    uint64_t winning_trades = 0;
    double total_pnl = 0.0;
    double largest_win = -numeric_limits<double>::max();
    double largest_loss = numeric_limits<double>::max();

    // For drawdown calculation
    double balance = static_cast<double>(initial_capital_);
    double peak_balance = balance;
    double max_drawdown = 0.0;
    
    // Loop through all trades
    for (const auto& trade : trades) {
        // Accumulate PnL
        total_pnl += trade.pnl;
        balance += trade.pnl;
        
        // Count winning trades
        if (trade.pnl > 0) {
            winning_trades++;
        }
        
        // Track largest win and loss
        largest_win = max(largest_win, trade.pnl);
        largest_loss = min(largest_loss, trade.pnl);
        
        // Track max drawdown
        if (balance > peak_balance) {
            peak_balance = balance;
        }
        double current_drawdown = peak_balance - balance;
        max_drawdown = max(max_drawdown, current_drawdown);
    }
    
    // Calculate win rate
    double win_rate = (static_cast<double>(winning_trades) / static_cast<double>(total_trades)) * 100.0;
    
    // Return statistics
    return Statistics{
        total_trades,
        winning_trades,
        total_pnl,
        win_rate,
        max_drawdown,
        largest_win,
        largest_loss
    };
}


