#include "Backtester.h"
#include "JSONdata.h"
#include "TechnicalAnalysis.h"
#include <iostream>
#include <memory>

// Enhanced Strategy combining MA Crossover with RSI and MACD filters
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
        
        if (dates.size() < longPeriod) {
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

        bool inPosition = false;
        bool isLong = false;

        // Run strategy
        for (size_t i = longPeriod; i < dates.size(); ++i) {
            if (std::isnan(shortMA[i]) || std::isnan(longMA[i]) || 
                std::isnan(rsi[i]) || std::isnan(macd[i]) || std::isnan(signal[i])) {
                continue;
            }

            // Check for crossover
            bool crossUp = shortMA[i] > longMA[i] && shortMA[i-1] <= longMA[i-1];
            bool crossDown = shortMA[i] < longMA[i] && shortMA[i-1] >= longMA[i-1];

            // Check RSI conditions
            bool rsiOversoldCondition = rsi[i] < rsiOversold;
            bool rsiOverboughtCondition = rsi[i] > rsiOverbought;

            // Check MACD conditions
            bool macdBullish = macd[i] > signal[i] && macd[i-1] <= signal[i-1];
            bool macdBearish = macd[i] < signal[i] && macd[i-1] >= signal[i-1];

            // Close existing position if there's a crossover or filter conditions are met
            if (inPosition) {
                if (isLong && (crossDown || rsiOverboughtCondition || macdBearish)) {
                    closeTrade(dates[i], closes[i]);
                    inPosition = false;
                } else if (!isLong && (crossUp || rsiOversoldCondition || macdBullish)) {
                    closeTrade(dates[i], closes[i]);
                    inPosition = false;
                }
            }

            // Open new position if all conditions align
            if (!inPosition) {
                if (crossUp && rsiOversoldCondition && macdBullish) {
                    executeTrade(dates[i], closes[i], true);  // Long position
                    inPosition = true;
                    isLong = true;
                } else if (crossDown && rsiOverboughtCondition && macdBearish) {
                    executeTrade(dates[i], closes[i], false); // Short position
                    inPosition = true;
                    isLong = false;
                }
            }
        }

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

int main() {
    try {
        // Fetch data using Python script
        std::string command = "python3 fetch_yahoo.py AAPL 1y 1d";
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        
        if (!pipe) {
            throw std::runtime_error("Failed to execute Python script");
        }

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }

        // Find the JSON part of the output
        size_t start = result.find('{');
        size_t end = result.rfind('}');
        if (start == std::string::npos || end == std::string::npos) {
            throw std::runtime_error("Invalid JSON output from Python script");
        }
        std::string jsonData = result.substr(start, end - start + 1);

        // Parse data
        JSONdata data;
        data.parseYahooData(jsonData);

        // Initialize technical analysis
        TechnicalAnalysis ta(data);

        // Create and run enhanced strategy
        EnhancedStrategy strategy(data, ta, 10000.0, 0.1);  // $10,000 initial capital, 10% position size
        strategy.setParameters(10, 20, 14, 70, 30);  // MA periods, RSI period, RSI levels
        strategy.runStrategy();

        // Print results
        strategy.printPerformanceReport();
        strategy.exportTradesToCSV("trades.csv");

        std::cout << "\nTrades have been exported to trades.csv\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} 