#include "../include/Backtester.h"
#include "../include/JSONdata.h"
#include "../include/TechnicalAnalysis.h"
#include "../include/Strategy.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <limits>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <filesystem>

// DEBUG VERSION: Prints indicator values and uses only MA crossover for entries
class EnhancedStrategy : public Backtester {
public:
    EnhancedStrategy(JSONdata& data, TechnicalAnalysis& ta, double initialCap, double posSize, StrategyType type = StrategyType::COMBINED)
        : Backtester(data, ta, initialCap, posSize)
        , shortPeriod(10)
        , longPeriod(20)
        , rsiPeriod(14)
        , rsiOverbought(70)
        , rsiOversold(30)
        , strategyType(type)
    {}

    void setParameters(int shortP, int longP, int rsiP, double rsiOver, double rsiUnder) {
        shortPeriod = shortP;
        longPeriod = longP;
        rsiPeriod = rsiP;
        rsiOverbought = rsiOver;
        rsiOversold = rsiUnder;
    }

    void runStrategy() override {
        if (strategyType == StrategyType::BEST_PERFORMER) {
            runAllStrategies();
            return;
        }

        // Get price data (for validation only)
        const auto& dates = historicalData.getDates();
        (void)dates; // Suppress unused variable warning

        if (dates.size() < static_cast<size_t>(longPeriod)) {
            throw std::runtime_error("Not enough data points for strategy");
        }

        switch(strategyType) {
            case StrategyType::SMA_CROSSOVER:
                runSMAStrategy();
                break;
            case StrategyType::RSI_REVERSAL:
                runRSIStrategy();
                break;
            case StrategyType::MACD_TREND:
                runMACDStrategy();
                break;
            case StrategyType::COMBINED:
                runCombinedStrategy();
                break;
            default:
                throw std::runtime_error("Invalid strategy type");
        }

        // Calculate performance metrics
        calculateMetrics();
    }

private:
    int shortPeriod;
    int longPeriod;
    int rsiPeriod;
    double rsiOverbought;
    double rsiOversold;
    StrategyType strategyType;

    // Individual strategy implementations
    void runSMAStrategy() {
        const auto& dates = historicalData.getDates();
        const auto& closes = historicalData.getClose();
        
        std::vector<double> shortMA = technicalAnalysis.calculateSMA(closes, shortPeriod);
        std::vector<double> longMA = technicalAnalysis.calculateSMA(closes, longPeriod);
        
        bool inPosition = false;
        
        for (size_t i = longPeriod; i < dates.size(); ++i) {
            // SMA Crossover logic
            bool bullishCross = shortMA[i-1] <= longMA[i-1] && shortMA[i] > longMA[i];
            bool bearishCross = shortMA[i-1] >= longMA[i-1] && shortMA[i] < longMA[i];
            
            if (!inPosition && bullishCross) {
                executeTrade(dates[i], closes[i], true);
                inPosition = true;
            }
            else if (inPosition && bearishCross) {
                closeTrade(dates[i], closes[i]);
                inPosition = false;
            }
        }
        if (inPosition) {
            closeTrade(dates.back(), closes.back());
        }
    }

    void runRSIStrategy() {
        const auto& dates = historicalData.getDates();
        const auto& closes = historicalData.getClose();
        
        technicalAnalysis.calcRSI(historicalData);
        std::vector<double> rsi;
        technicalAnalysis.getRSI(rsi);
        
        bool inPosition = false;
        
        for (size_t i = rsiPeriod; i < dates.size(); ++i) {
            // RSI mean reversion logic
            bool oversold = rsi[i] < rsiOversold;
            bool overbought = rsi[i] > rsiOverbought;
            
            if (!inPosition && oversold) {
                executeTrade(dates[i], closes[i], true);
                inPosition = true;
            }
            else if (inPosition && overbought) {
                closeTrade(dates[i], closes[i]);
                inPosition = false;
            }
        }
        if (inPosition) {
            closeTrade(dates.back(), closes.back());
        }
    }

    void runMACDStrategy() {
        const auto& dates = historicalData.getDates();
        const auto& closes = historicalData.getClose();
        
        technicalAnalysis.calcMACD(historicalData);
        std::vector<double> macd, signal;
        technicalAnalysis.getMACD(macd);
        technicalAnalysis.getSignal(signal);
        
        bool inPosition = false;
        
        for (size_t i = 26; i < dates.size(); ++i) {  // MACD uses 26 periods
            // MACD Trend following logic
            bool bullishCross = macd[i-1] <= signal[i-1] && macd[i] > signal[i];
            bool bearishCross = macd[i-1] >= signal[i-1] && macd[i] < signal[i];
            
            if (!inPosition && bullishCross) {
                executeTrade(dates[i], closes[i], true);
                inPosition = true;
            }
            else if (inPosition && bearishCross) {
                closeTrade(dates[i], closes[i]);
                inPosition = false;
            }
        }
        if (inPosition) {
            closeTrade(dates.back(), closes.back());
        }
    }

    void runCombinedStrategy() {
        const auto& dates = historicalData.getDates();
        const auto& closes = historicalData.getClose();
        
        // Calculate all indicators
        std::vector<double> shortMA = technicalAnalysis.calculateSMA(closes, shortPeriod);
        std::vector<double> longMA = technicalAnalysis.calculateSMA(closes, longPeriod);
        
        technicalAnalysis.calcRSI(historicalData);
        std::vector<double> rsi;
        technicalAnalysis.getRSI(rsi);
        
        technicalAnalysis.calcMACD(historicalData);
        std::vector<double> macd, signal;
        technicalAnalysis.getMACD(macd);
        technicalAnalysis.getSignal(signal);
        
        bool inPosition = false;
        
        for (size_t i = std::max(longPeriod, 26); i < dates.size(); ++i) {
            // Combined strategy logic
            bool smaBullish = shortMA[i-1] <= longMA[i-1] && shortMA[i] > longMA[i];
            bool smaBearish = shortMA[i-1] >= longMA[i-1] && shortMA[i] < longMA[i];
            
            bool rsiBullish = rsi[i] < rsiOversold;
            bool rsiBearish = rsi[i] > rsiOverbought;
            
            bool macdBullish = macd[i-1] <= signal[i-1] && macd[i] > signal[i];
            bool macdBearish = macd[i-1] >= signal[i-1] && macd[i] < signal[i];
            
            if (!inPosition && (smaBullish && rsiBullish && macdBullish)) {
                executeTrade(dates[i], closes[i], true);
                inPosition = true;
            }
            else if (inPosition && (smaBearish && rsiBearish && macdBearish)) {
                closeTrade(dates[i], closes[i]);
                inPosition = false;
            }
        }
        if (inPosition) {
            closeTrade(dates.back(), closes.back());
        }
    }

    void runAllStrategies() {
        // Store original state (for potential restoration if needed)
        auto originalTrades = trades;
        (void)originalTrades; // Suppress unused variable warning
        
        std::vector<StrategyResult> results;
        
        // Run each strategy and store results
        std::vector<StrategyType> strategies = {
            StrategyType::SMA_CROSSOVER,
            StrategyType::RSI_REVERSAL,
            StrategyType::MACD_TREND,
            StrategyType::COMBINED
        };
        
        for (auto strat : strategies) {
            trades.clear();
            strategyType = strat;
            
            switch(strat) {
                case StrategyType::SMA_CROSSOVER: runSMAStrategy(); break;
                case StrategyType::RSI_REVERSAL: runRSIStrategy(); break;
                case StrategyType::MACD_TREND: runMACDStrategy(); break;
                case StrategyType::COMBINED: runCombinedStrategy(); break;
                default: continue;
            }
            
            calculateMetrics();
            
            results.push_back({
                strat,
                metrics.totalReturn,
                metrics.sharpeRatio,
                metrics.totalTrades,
                metrics.winRate
            });
        }
        
        // Find best strategy based on Sharpe ratio
        auto bestStrategy = *std::max_element(results.begin(), results.end(),
            [](const StrategyResult& a, const StrategyResult& b) {
                return a.sharpeRatio < b.sharpeRatio;
            });
        
        // Print comparison table
        std::cout << "\n=== Strategy Comparison ===\n";
        std::cout << std::setw(15) << "Strategy" 
                  << std::setw(15) << "Return (%)" 
                  << std::setw(15) << "Sharpe"
                  << std::setw(15) << "# Trades"
                  << std::setw(15) << "Win Rate (%)\n";
        std::cout << std::string(75, '-') << "\n";
        
        for (const auto& result : results) {
            std::string stratName;
            switch(result.type) {
                case StrategyType::SMA_CROSSOVER: stratName = "SMA"; break;
                case StrategyType::RSI_REVERSAL: stratName = "RSI"; break;
                case StrategyType::MACD_TREND: stratName = "MACD"; break;
                case StrategyType::COMBINED: stratName = "Combined"; break;
                default: stratName = "Unknown"; break;
            }
            
            std::cout << std::setw(15) << stratName
                      << std::setw(15) << std::fixed << std::setprecision(2) << result.totalReturn
                      << std::setw(15) << std::fixed << std::setprecision(2) << result.sharpeRatio
                      << std::setw(15) << result.totalTrades
                      << std::setw(15) << std::fixed << std::setprecision(2) << result.winRate << "\n";
        }
        
        std::cout << "\nBest Strategy: ";
        switch(bestStrategy.type) {
            case StrategyType::SMA_CROSSOVER: std::cout << "SMA Crossover"; break;
            case StrategyType::RSI_REVERSAL: std::cout << "RSI Reversal"; break;
            case StrategyType::MACD_TREND: std::cout << "MACD Trend"; break;
            case StrategyType::COMBINED: std::cout << "Combined"; break;
            default: std::cout << "Unknown"; break;
        }
        std::cout << " (Sharpe: " << std::fixed << std::setprecision(2) << bestStrategy.sharpeRatio << ")\n\n";
        
        // Run best strategy again to update final metrics
        trades.clear();
        strategyType = bestStrategy.type;
        switch(bestStrategy.type) {
            case StrategyType::SMA_CROSSOVER: runSMAStrategy(); break;
            case StrategyType::RSI_REVERSAL: runRSIStrategy(); break;
            case StrategyType::MACD_TREND: runMACDStrategy(); break;
            case StrategyType::COMBINED: runCombinedStrategy(); break;
            default: break;
        }
    }
};

int main(int argc, char* argv[]) {
    try {
        // Parse command-line arguments for symbol and period
        std::string symbol = "AAPL";  // Default symbol
        std::string period = "1y";    // Default period
        
        // Valid periods
        const std::vector<std::string> validPeriods = {"1mo", "3mo", "6mo", "1y", "2y", "5y"};
        
        // Check if arguments are provided
        if (argc > 1) {
            symbol = argv[1];
        } else {
            // If no arguments provided, ask user for input
            std::cout << "Enter stock symbol (default: AAPL): ";
            std::string input;
            std::getline(std::cin, input);
            if (!input.empty()) {
                symbol = input;
            }
        }
        
        if (argc > 2) {
            period = argv[2];
            // Validate period
            if (std::find(validPeriods.begin(), validPeriods.end(), period) == validPeriods.end()) {
                std::cerr << "Error: Invalid period. Valid periods are: 1mo, 3mo, 6mo, 1y, 2y, 5y\n";
                return 1;
            }
        } else {
            // If no period provided, ask user for input
            std::cout << "Enter time period (1mo, 3mo, 6mo, 1y, 2y, 5y) (default: 1y): ";
            std::string input;
            std::getline(std::cin, input);
            if (!input.empty()) {
                if (std::find(validPeriods.begin(), validPeriods.end(), input) == validPeriods.end()) {
                    std::cerr << "Error: Invalid period. Valid periods are: 1mo, 3mo, 6mo, 1y, 2y, 5y\n";
                    return 1;
                }
                period = input;
            }
        }

        std::cout << "Running backtest for " << symbol << " over " << period << " period\n";

        // Load data from pre-downloaded JSON file
        std::string filename = "data/" + symbol + "_" + period + ".json";
        std::cout << "Loading data from: " << filename << std::endl;

        JSONdata data;
        if (!data.loadFromFile(filename)) {
            std::cerr << "Error: Could not load data file " << filename << std::endl;
            std::cerr << "Please ensure the file exists. You can create it by running:" << std::endl;
            std::cerr << "python3 src/fetch_yahoo.py " << symbol << " " << period << " 1d > " << filename << std::endl;
            return 1;
        }

        std::cout << "Data loaded successfully!" << std::endl;

        // Display data range information
        const auto& dates = data.getDates();
        if (!dates.empty()) {
            std::cout << "📅 Data Range: " << dates.front() << " to " << dates.back()
                      << " (" << dates.size() << " trading days)" << std::endl;
        }

        // Initialize technical analysis
        TechnicalAnalysis ta(data);

        // Strategy selection
        StrategyType selectedStrategy = StrategyType::COMBINED;  // Default

        std::cout << "\nSelect trading strategy:\n";
        std::cout << "1. SMA Crossover (Simple Moving Average)\n";
        std::cout << "2. RSI Reversal (Mean Reversion)\n";
        std::cout << "3. MACD Trend Following\n";
        std::cout << "4. Combined Strategy (All indicators)\n";
        std::cout << "5. Best Performer (Test all and pick best)\n";
        std::cout << "Enter choice (1-5, default: 4): ";

        std::string choice;
        std::getline(std::cin, choice);

        if (!choice.empty()) {
            int stratChoice = std::stoi(choice);
            switch(stratChoice) {
                case 1: selectedStrategy = StrategyType::SMA_CROSSOVER; break;
                case 2: selectedStrategy = StrategyType::RSI_REVERSAL; break;
                case 3: selectedStrategy = StrategyType::MACD_TREND; break;
                case 4: selectedStrategy = StrategyType::COMBINED; break;
                case 5: selectedStrategy = StrategyType::BEST_PERFORMER; break;
                default:
                    std::cout << "Invalid choice, using Combined Strategy\n";
                    selectedStrategy = StrategyType::COMBINED;
                    break;
            }
        }

        // Create and run enhanced strategy
        EnhancedStrategy strategy(data, ta, 10000.0, 0.1, selectedStrategy);  // $10,000 initial capital, 10% position size
        strategy.setParameters(10, 20, 14, 70, 30);  // MA periods, RSI period, RSI levels
        strategy.runStrategy();

        // Print results
        strategy.printPerformanceReport();
        std::cout << "\nTrades have been exported to trades.csv (if you choose to save them)\n";

        // Prompt user to save report and trades
        std::cout << "\nDo you want to save the performance report and trades to files? (y/n): ";
        std::string exportChoice;
        std::getline(std::cin, exportChoice);
        if (exportChoice == "y" || exportChoice == "Y") {
            // Create performance_reports directory if it doesn't exist
            std::filesystem::create_directories("performance_reports");
            
            // Create unique filenames based on symbol and period
            std::string reportFilename = "performance_reports/performance_" + symbol + "_" + period + ".txt";
            std::string tradesFilename = "performance_reports/trades_" + symbol + "_" + period + ".csv";
            
            // Save performance report
            std::ofstream reportFile(reportFilename);
            if (reportFile.is_open()) {
                reportFile << "=== Performance Report ===\n";
                reportFile << "Symbol: " << symbol << "\n";
                reportFile << "Duration: " << period << "\n";
                reportFile << std::fixed << std::setprecision(2);
                reportFile << "Initial Capital: $" << strategy.getInitialCapital() << "\n";
                reportFile << "Final Capital: $" << strategy.getCurrentCapital() << "\n";
                reportFile << "Total Return: " << strategy.getMetrics().totalReturn << "%\n";
                reportFile << "Annualized Return: " << strategy.getMetrics().annualizedReturn << "%\n";
                reportFile << "Sharpe Ratio: " << strategy.getMetrics().sharpeRatio << "\n";
                reportFile << "Maximum Drawdown: " << strategy.getMetrics().maxDrawdown << "%\n";
                reportFile << "\nTrade Statistics:\n";
                reportFile << "Total Trades: " << strategy.getMetrics().totalTrades << "\n";
                reportFile << "Winning Trades: " << strategy.getMetrics().winningTrades << "\n";
                reportFile << "Losing Trades: " << strategy.getMetrics().losingTrades << "\n";
                reportFile << "Win Rate: " << strategy.getMetrics().winRate << "%\n";
                reportFile << "Profit Factor: " << strategy.getMetrics().profitFactor << "\n";
                reportFile << "Average Win: $" << strategy.getMetrics().averageWin << "\n";
                reportFile << "Average Loss: $" << strategy.getMetrics().averageLoss << "\n";
                reportFile << "Largest Win: $" << strategy.getMetrics().largestWin << "\n";
                reportFile << "Largest Loss: $" << strategy.getMetrics().largestLoss << "\n";
                reportFile << "========================\n";
                reportFile.close();
                std::cout << "Performance report saved to " << reportFilename << "\n";
            }

            // Save trades to CSV
            strategy.exportTradesToCSV(tradesFilename);
            std::cout << "Trades saved to " << tradesFilename << "\n";
        } else {
            std::cout << "Results not saved to files.\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} 