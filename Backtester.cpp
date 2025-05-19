#include "Backtester.h"
#include <fstream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>

Backtester::Backtester(JSONdata& data, TechnicalAnalysis& ta, double initialCap, double posSize)
    : historicalData(data)
    , technicalAnalysis(ta)
    , initialCapital(initialCap)
    , currentCapital(initialCap)
    , positionSize(posSize)
{
    // Initialize metrics
    metrics = PerformanceMetrics{
        0.0,    // totalReturn
        0.0,    // annualizedReturn
        0.0,    // sharpeRatio
        0.0,    // maxDrawdown
        0.0,    // winRate
        0.0,    // profitFactor
        0.0,    // averageWin
        0.0,    // averageLoss
        0.0,    // largestWin
        0.0,    // largestLoss
        0,      // totalTrades
        0,      // winningTrades
        0       // losingTrades
    };
}

void Backtester::executeTrade(const std::string& date, double price, bool isLong) {
    Trade trade;
    trade.entryDate = date;
    trade.entryPrice = price;
    trade.positionSize = (currentCapital * positionSize) / price;  // Calculate number of shares
    trade.isLong = isLong;
    trade.exitDate = "";
    trade.exitPrice = 0.0;
    trade.profitLoss = 0.0;
    trade.profitLossPct = 0.0;
    
    trades.push_back(trade);
}

void Backtester::closeTrade(const std::string& date, double price) {
    if (trades.empty() || !trades.back().exitDate.empty()) {
        return;  // No open trade to close
    }
    
    Trade& trade = trades.back();
    trade.exitDate = date;
    trade.exitPrice = price;
    
    // Calculate profit/loss
    if (trade.isLong) {
        trade.profitLoss = (price - trade.entryPrice) * trade.positionSize;
    } else {
        trade.profitLoss = (trade.entryPrice - price) * trade.positionSize;
    }
    
    trade.profitLossPct = (trade.profitLoss / (trade.entryPrice * trade.positionSize)) * 100.0;
    currentCapital += trade.profitLoss;
}

void Backtester::calculateMetrics() {
    if (trades.empty()) {
        return;
    }
    
    // Calculate basic metrics
    metrics.totalTrades = trades.size();
    metrics.winningTrades = std::count_if(trades.begin(), trades.end(), 
        [](const Trade& t) { return t.profitLoss > 0; });
    metrics.losingTrades = metrics.totalTrades - metrics.winningTrades;
    
    metrics.winRate = (static_cast<double>(metrics.winningTrades) / metrics.totalTrades) * 100.0;
    
    // Calculate profit metrics
    double totalProfit = 0.0;
    double totalLoss = 0.0;
    std::vector<double> returns;
    
    for (const auto& trade : trades) {
        if (trade.profitLoss > 0) {
            totalProfit += trade.profitLoss;
            metrics.averageWin += trade.profitLoss;
            metrics.largestWin = std::max(metrics.largestWin, trade.profitLoss);
        } else {
            totalLoss += std::abs(trade.profitLoss);
            metrics.averageLoss += std::abs(trade.profitLoss);
            metrics.largestLoss = std::min(metrics.largestLoss, trade.profitLoss);
        }
        returns.push_back(trade.profitLossPct);
    }
    
    // Calculate averages
    if (metrics.winningTrades > 0) {
        metrics.averageWin /= metrics.winningTrades;
    }
    if (metrics.losingTrades > 0) {
        metrics.averageLoss /= metrics.losingTrades;
    }
    
    // Calculate profit factor
    metrics.profitFactor = (totalLoss > 0) ? (totalProfit / totalLoss) : 0.0;
    
    // Calculate returns
    metrics.totalReturn = ((currentCapital - initialCapital) / initialCapital) * 100.0;
    
    // Calculate annualized return (assuming 252 trading days per year)
    double days = (trades.back().exitDate > trades.front().entryDate) ? 
        std::stod(trades.back().exitDate) - std::stod(trades.front().entryDate) : 1.0;
    metrics.annualizedReturn = (std::pow(1.0 + metrics.totalReturn/100.0, 252.0/days) - 1.0) * 100.0;
    
    // Calculate Sharpe Ratio
    metrics.sharpeRatio = calculateSharpeRatio(returns);
    
    // Calculate maximum drawdown
    double peak = initialCapital;
    double maxDrawdown = 0.0;
    double currentValue = initialCapital;
    
    for (const auto& trade : trades) {
        currentValue += trade.profitLoss;
        if (currentValue > peak) {
            peak = currentValue;
        }
        double drawdown = (peak - currentValue) / peak * 100.0;
        maxDrawdown = std::max(maxDrawdown, drawdown);
    }
    metrics.maxDrawdown = maxDrawdown;
}

double Backtester::calculateSharpeRatio(const std::vector<double>& returns) {
    if (returns.empty()) return 0.0;
    
    // Calculate mean return
    double mean = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    
    // Calculate standard deviation
    double variance = std::accumulate(returns.begin(), returns.end(), 0.0,
        [mean](double acc, double ret) { return acc + std::pow(ret - mean, 2); }) / returns.size();
    double stdDev = std::sqrt(variance);
    
    // Calculate Sharpe Ratio (assuming risk-free rate of 0 for simplicity)
    return (stdDev > 0) ? (mean / stdDev) * std::sqrt(252.0) : 0.0;
}

void Backtester::exportTradesToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }
    
    // Write header
    file << "Entry Date,Exit Date,Entry Price,Exit Price,Position Size,Profit/Loss,Profit/Loss %,Direction\n";
    
    // Write trades
    for (const auto& trade : trades) {
        file << trade.entryDate << ","
             << trade.exitDate << ","
             << std::fixed << std::setprecision(2) << trade.entryPrice << ","
             << trade.exitPrice << ","
             << trade.positionSize << ","
             << trade.profitLoss << ","
             << trade.profitLossPct << ","
             << (trade.isLong ? "LONG" : "SHORT") << "\n";
    }
}

void Backtester::printPerformanceReport() const {
    std::cout << "\n=== Performance Report ===\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Initial Capital: $" << initialCapital << "\n";
    std::cout << "Final Capital: $" << currentCapital << "\n";
    std::cout << "Total Return: " << metrics.totalReturn << "%\n";
    std::cout << "Annualized Return: " << metrics.annualizedReturn << "%\n";
    std::cout << "Sharpe Ratio: " << metrics.sharpeRatio << "\n";
    std::cout << "Maximum Drawdown: " << metrics.maxDrawdown << "%\n";
    std::cout << "\nTrade Statistics:\n";
    std::cout << "Total Trades: " << metrics.totalTrades << "\n";
    std::cout << "Winning Trades: " << metrics.winningTrades << "\n";
    std::cout << "Losing Trades: " << metrics.losingTrades << "\n";
    std::cout << "Win Rate: " << metrics.winRate << "%\n";
    std::cout << "Profit Factor: " << metrics.profitFactor << "\n";
    std::cout << "Average Win: $" << metrics.averageWin << "\n";
    std::cout << "Average Loss: $" << metrics.averageLoss << "\n";
    std::cout << "Largest Win: $" << metrics.largestWin << "\n";
    std::cout << "Largest Loss: $" << metrics.largestLoss << "\n";
    std::cout << "========================\n";
}

// Note: runStrategy() will be implemented in a separate file for specific strategies
void Backtester::runStrategy() {
    // This is a placeholder - specific strategy implementations will be added later
    throw std::runtime_error("Strategy not implemented");
} 