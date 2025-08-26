#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include <string>
#include "JSONdata.h"
#include "TechnicalAnalysis.h"

enum class StrategyType {
    SMA_CROSSOVER,    // Simple Moving Average Crossover
    RSI_REVERSAL,     // RSI-based mean reversion
    MACD_TREND,       // MACD Trend Following
    COMBINED,         // All strategies combined (original approach)
    BEST_PERFORMER    // Run all and pick the best
};

struct StrategyResult {
    StrategyType type;
    double totalReturn;
    double sharpeRatio;
    int totalTrades;
    double winRate;
    
    StrategyResult(StrategyType t, double ret, double sharpe, int trades, double win) 
        : type(t), totalReturn(ret), sharpeRatio(sharpe), totalTrades(trades), winRate(win) {}
};

#endif // STRATEGY_H
