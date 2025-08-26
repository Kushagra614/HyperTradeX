#ifndef BACKTESTER_H
#define BACKTESTER_H

#include "JSONdata.h"
#include "TechnicalAnalysis.h"
#include <vector>
#include <string>
#include <map>
#include <memory>

// Structure to hold trade information
struct Trade {
    std::string entryDate;
    std::string exitDate;
    double entryPrice;
    double exitPrice;
    double positionSize;  // Number of shares
    double profitLoss;    // In dollars
    double profitLossPct; // As percentage
    bool isLong;         // true for long, false for short
};

// Structure to hold performance metrics
struct PerformanceMetrics {
    double totalReturn;           // Total return as percentage
    double annualizedReturn;      // Annualized return
    double sharpeRatio;          // Risk-adjusted return metric
    double maxDrawdown;          // Maximum drawdown as percentage
    double winRate;              // Percentage of winning trades
    double profitFactor;         // Gross profit / gross loss
    double averageWin;           // Average winning trade in dollars
    double averageLoss;          // Average losing trade in dollars
    double largestWin;           // Largest winning trade in dollars
    double largestLoss;          // Largest losing trade in dollars
    int totalTrades;            // Total number of trades
    int winningTrades;          // Number of winning trades
    int losingTrades;           // Number of losing trades
};

// Strategy enum moved to Strategy.h

#include "Strategy.h"

class Backtester {
protected:
    JSONdata& historicalData;
    TechnicalAnalysis& technicalAnalysis;
    std::vector<Trade> trades;
    PerformanceMetrics metrics;
    double initialCapital;
    double currentCapital;
    double positionSize;  // Fixed position size for each trade
    StrategyType activeStrategy;
    
    // Helper functions
    void calculateMetrics();
    void updateDrawdown(double currentValue);
    double calculateSharpeRatio(const std::vector<double>& returns);
    void executeTrade(const std::string& date, double price, bool isLong);
    void closeTrade(const std::string& date, double price);
    
public:
    Backtester(JSONdata& data, TechnicalAnalysis& ta, double initialCap = 100000.0, double posSize = 0.1);
    
    // Strategy execution
    virtual void runStrategy() = 0;  // Changed to pure virtual function
    
    // Performance analysis
    const PerformanceMetrics& getMetrics() const { return metrics; }
    const std::vector<Trade>& getTrades() const { return trades; }
    
    // Export results
    void exportTradesToCSV(const std::string& filename) const;
    void printPerformanceReport() const;
    
    // Strategy parameters
    void setPositionSize(double size) { positionSize = size; }
    double getPositionSize() const { return positionSize; }
    void setInitialCapital(double capital) { initialCapital = capital; currentCapital = capital; }
    double getInitialCapital() const { return initialCapital; }
    double getCurrentCapital() const { return currentCapital; }
};

#endif // BACKTESTER_H 