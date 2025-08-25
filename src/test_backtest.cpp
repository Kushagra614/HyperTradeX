#include "../include/Backtester.h"
#include "../include/JSONdata.h"
#include "../include/TechnicalAnalysis.h"
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
    EnhancedStrategy(JSONdata& data, TechnicalAnalysis& ta, double initialCap, double posSize)
        : Backtester(data, ta, initialCap, posSize)
        , shortPeriod(10)
        , longPeriod(20)
        , rsiPeriod(14)
        , rsiOverbought(70)
        , rsiOversold(30)
    {}

    void setParameters(int shortP, int longP, int rsiP, double rsiOver, double rsiUnder) {
        shortPeriod = shortP;
        longPeriod = longP;
        rsiPeriod = rsiP;
        rsiOverbought = rsiOver;
        rsiOversold = rsiUnder;
    }

    void runStrategy() override {
        // Get price data
        const auto& dates = historicalData.getDates();
        const auto& closes = historicalData.getClose();
        
        if (dates.size() < static_cast<size_t>(longPeriod)) {
            throw std::runtime_error("Not enough data points for strategy");
        }

        // Calculate indicators
        std::vector<double> shortMA = technicalAnalysis.calculateSMA(closes, shortPeriod);
        std::vector<double> longMA = technicalAnalysis.calculateSMA(closes, longPeriod);
        
        // Calculate RSI
        technicalAnalysis.calcRSI(historicalData);
        std::vector<double> rsi;
        technicalAnalysis.getRSI(rsi);
        
        // Calculate MACD
        technicalAnalysis.calcMACD(historicalData);
        std::vector<double> macd, signal;
        technicalAnalysis.getMACD(macd);
        technicalAnalysis.getSignal(signal);

        // Print indicator sizes for debugging
        std::cout << "shortMA size: " << shortMA.size() << ", longMA size: " << longMA.size()
                  << ", rsi size: " << rsi.size() << ", macd size: " << macd.size()
                  << ", signal size: " << signal.size() << std::endl;

        bool inPosition = false;
        bool isLong = false;

        // Run strategy
        int validDays = 0;
        for (size_t i = longPeriod; i < dates.size(); ++i) {
            if (std::isnan(shortMA[i]) || std::isnan(longMA[i])) {
                continue;
            }
            validDays++;

            // Check for crossover
            bool crossUp = shortMA[i] > longMA[i] && shortMA[i-1] <= longMA[i-1];
            bool crossDown = shortMA[i] < longMA[i] && shortMA[i-1] >= longMA[i-1];

            // Close existing position if there's a crossover or filter conditions are met
            if (inPosition) {
                if (isLong && (crossDown /*|| rsiOverboughtCondition || macdBearish*/)) {
                    closeTrade(dates[i], closes[i]);
                    inPosition = false;
                } else if (!isLong && (crossUp /*|| rsiOversoldCondition || macdBullish*/)) {
                    closeTrade(dates[i], closes[i]);
                    inPosition = false;
                }
            }

            // Open new position if all conditions align (loosened: just MA crossover)
            if (!inPosition) {
                if (crossUp /*&& rsiOversoldCondition && macdBullish*/) {
                    executeTrade(dates[i], closes[i], true);  // Long position
                    inPosition = true;
                    isLong = true;
                } else if (crossDown /*&& rsiOverboughtCondition && macdBearish*/) {
                    executeTrade(dates[i], closes[i], false); // Short position
                    inPosition = true;
                    isLong = false;
                }
            }
        }
        std::cout << "\nValid days processed: " << validDays << std::endl;

        // Close any open position at the end
        if (inPosition) {
            closeTrade(dates.back(), closes.back());
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

        // Initialize technical analysis
        TechnicalAnalysis ta(data);

        // Create and run enhanced strategy
        EnhancedStrategy strategy(data, ta, 10000.0, 0.1);  // $10,000 initial capital, 10% position size
        strategy.setParameters(10, 20, 14, 70, 30);  // MA periods, RSI period, RSI levels
        strategy.runStrategy();

        // Print results
        strategy.printPerformanceReport();
        std::cout << "\nTrades have been exported to trades.csv (if you choose to save them)\n";

        // Prompt user to save report and trades
        std::cout << "\nDo you want to save the performance report and trades to files? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
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