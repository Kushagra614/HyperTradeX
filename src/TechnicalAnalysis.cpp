#include "../include/TechnicalAnalysis.h"
#include <limits>

/* TODO STILL UNDER CONSTRUCTION
   void TechnicalAnalysis::calcSD()
   {
    double sum = 0.0, mean, standardDeviation = 0.0;

    for(int i = 0; i < 10; ++i)
        sum += data[i];

    mean = sum/10;

    for(i = 0; i < 10; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / 10);
   }

 */

/* TODO MACD IS STILL UNDER CONSTRUCTION
void TechnicalAnalysis::calcMACD(JSONdata &HistoricalData)
{
  assert(!HistoricalData.isEmpty());

  calcMACD_EMA(HistoricalData, 26);
  std::vector<double> 26_EMA = MACD_EMA;
  MACD_EMA.clear();

  calcMACD_EMA(HistoricalData, 12);
  std::vector<double> 12_EMA = MACD_EMA;
  MACD_EMA.clear();

  for(int i = 0; i < 26_EMA.size(); i++)
    accessMACD(12_EMA[i] - 26_EMA[i]);

  calcMACD_EMA(HistoricalData, 9);

  for(int i = 0; i < MACD_EMA.size(); i++)
    accessSignal(MACD_EMA[i]);

  MACD_EMA.clear();
}

//TODO this should probably be how all EMA/SMA's are done.
void TechnicalAnalysis::calcMACD_EMA(JSONdata &HistoricalData, const int &period)
{
        assert(!HistoricalData.isEmpty());

        double SMA = 0.0, sum = 0.0, multipler = 0.0;
        int j = 0;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY EMA YET";
          return;
        }

        for(int i = 0; i < period; i++)
                sum += closePrices[i];

        SMA = sum/period;
        MACD_EMA.push_back(SMA);

        multipler = 2/(period + 1);

        for(int i = period; i <= (closePrices.size() - period); i++) {
                MACD_EMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
                j++;
        }
}
*/

/*-------------------- START EMAs --------------------*/
void TechnicalAnalysis::calcFiftyEMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());

        double SMA = 0.0, sum = 0.0, multipler = 0.0;
        const size_t period = 50;
        size_t j = 0;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY EMA YET";
          return;
        }

        std::vector<double> tempEMA;

        for(size_t i = 0; i < period; i++)
                sum += closePrices[i];

        SMA = sum/period;
        tempEMA.push_back(SMA);
        setFifEMA(SMA);
        multipler = 2/(period + 1);

        for(size_t i = period; i <= (closePrices.size() - period); i++) {
                tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
                j++;
                setFifEMA(tempEMA[j]);
        }
}

void TechnicalAnalysis::calcHundredEMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());

        double SMA = 0.0, sum = 0.0, multipler = 0.0;
        const size_t period = 100;
        size_t j = 0;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY EMA YET";
          return;
        }

        std::vector<double> tempEMA;

        for(size_t i = 0; i < period; i++)
                sum += closePrices[i];

        SMA = sum/period;
        tempEMA.push_back(SMA);
        setHundEMA(SMA);
        multipler = 2/(period + 1);

        for(size_t i = period; i <= (closePrices.size() - period); i++) {
                tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
                j++;
                setHundEMA(tempEMA[j]);
        }
}

void TechnicalAnalysis::calcHundFiftyEMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());

        double SMA = 0.0, sum = 0.0, multipler = 0.0;
        const size_t period = 150;
        size_t j = 0;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY EMA YET";
          return;
        }

        std::vector<double> tempEMA;

        for(size_t i = 0; i < period; i++)
                sum += closePrices[i];

        SMA = sum/period;
        tempEMA.push_back(SMA);
        setHundFifEMA(SMA);
        multipler = 2/(period + 1);

        for(size_t i = period; i <= (closePrices.size() - period); i++) {
                tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
                j++;
                setHundFifEMA(tempEMA[j]);
        }
}

void TechnicalAnalysis::calcTwoHundEMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());
        double SMA = 0.0, sum = 0.0, multipler = 0.0;
        const size_t period = 200;
        size_t j = 0;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY EMA YET";
          return;
        }

        std::vector<double> tempEMA;

        for(size_t i = 0; i < period; i++)
                sum += closePrices[i];

        SMA = sum/period;
        tempEMA.push_back(SMA);
        setTwoHundEMA(SMA);
        multipler = 2/(period + 1);

        for(size_t i = period; i <= (closePrices.size() - period); i++) {
                tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
                j++;
                setTwoHundEMA(tempEMA[j]);
        }
}

/*-------------------- END EMAs   --------------------*/


/*-------------------- START SMAs --------------------*/
void TechnicalAnalysis::calcFiftySMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());
        double sum;
        const size_t period = 50;

        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices,boost::none);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY SMA YET";
          return;
        }

        for(size_t i = 0; i <= (closePrices.size() - period); i++) {
                sum = 0.0;

                for (size_t j = i; j < i + period; j++)
                        sum += closePrices[j];

                setFifSMA(sum/period);
        }
}


void TechnicalAnalysis::calcHundredSMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());
        double sum;
        const size_t period = 100;

        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY SMA YET";
          return;
        }

        for(size_t i = 0; i <= (closePrices.size() - period); i++) {
                sum = 0.0;

                for (size_t j = i; j < i + period; j++)
                        sum += closePrices[j];

                setHundSMA(sum/period);
        }
}

void TechnicalAnalysis::calcHundFiftySMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());
        double sum;
        const size_t period = 150;

        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY SMA YET";
          return;
        }

        for(size_t i = 0; i <= (closePrices.size() - period); i++) {
                sum = 0.0;

                for (size_t j = i; j < i + period; j++)
                        sum += closePrices[j];

                setHundFifSMA(sum/period);
        }
}

void TechnicalAnalysis::calcTwoHundSMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());
        double sum;
        const size_t period = 200;

        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY SMA YET";
          return;
        }

        for(size_t i = 0; i <= (closePrices.size() - period); i++) {
                sum = 0.0;

                for (size_t j = i; j < i + period; j++)
                        sum += closePrices[j];

                setTwoHundSMA(sum/period);
        }
}
/*-------------------- END SMAs   --------------------*/


/*-------------------- START RSI  --------------------*/
void TechnicalAnalysis::calcRSI(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());

        auto pushCurrentPeriod = [] (const std::vector<long double> &currPeri, std::vector<long double> &change){
                                         for(size_t i = 1; i < currPeri.size(); i++)
                                                 change.push_back(currPeri[i] - currPeri[i-1]);
                                 };

        std::vector<long double> gain, loss, change, avgGain, avgLoss, RS;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        //We need these if/else statements so program works when there hasn't been 250 data points yet.
        if(closePrices.size() > 250) {
                std::vector <long double> currentPeriod(closePrices.end()-250,closePrices.end());
                pushCurrentPeriod(currentPeriod, change);
        }
        else{
                std::vector <long double> currentPeriod(closePrices.begin(),closePrices.end());
                pushCurrentPeriod(currentPeriod, change);
        }

        double sumGain = 0, sumLoss = 0;

        for(size_t i = 0; i < change.size(); i++) {
                change[i] > 0 ? gain.push_back(change[i]) : gain.push_back(0);
                change[i] < 0 ? loss.push_back(abs(change[i])) : loss.push_back(0);
                sumGain += gain[i];
                sumLoss += loss[i];
        }

        avgGain.push_back(sumGain/14);
        avgLoss.push_back(sumLoss/14);

        for(size_t i = 14, j = 1; i < gain.size(); i++) {
                avgGain.push_back(((avgGain[j-1] * 13)+ gain[i])/14);
                avgLoss.push_back(((avgLoss[j-1] * 13)+ loss[i])/14);
                j++;
        }

        for(size_t i = 0; i < avgGain.size(); i++) {
                RS.push_back(avgGain[i]/avgLoss[i]);
                setRSI(avgLoss[i] == 0 ? 100 : 100 - (100/(1+RS[i])));
        }
        calcStochRSI();
}

void TechnicalAnalysis::calcStochRSI()
{
        assert(!indicators.RSI.empty());

        auto copy = [] (const std::vector<double> &RSI, std::vector<double> &temp, const size_t &loc){
                            for(size_t i = 13; i != static_cast<size_t>(-1); i--)
                                    temp.push_back(RSI[loc-i]);
                    };

        std::vector<double> tempVec, tempRSI;
        getRSI(tempRSI);

        for(size_t i = 13; i < tempRSI.size(); i++) {
                copy(tempRSI,tempVec,i);
                auto lowIt= *std::min_element(tempVec.begin(), tempVec.end());
                auto highIt= *std::max_element(tempVec.begin(), tempVec.end());
                setStoch((tempVec.back()-lowIt)/(highIt-lowIt));
                tempVec.clear();
        }
}
/*-------------------- END RSI  --------------------*/

std::vector<double> TechnicalAnalysis::calculateSMA(const std::vector<double>& prices, size_t period) const {
    std::vector<double> sma;
    if (prices.size() < period) {
        return sma;
    }
    
    // Calculate first SMA
    double sum = 0.0;
    for (size_t i = 0; i < period; ++i) {
        sum += prices[i];
    }
    sma.push_back(sum / period);
    
    // Calculate remaining SMAs using the previous value
    for (size_t i = period; i < prices.size(); ++i) {
        sum = sum - prices[i - period] + prices[i];
        sma.push_back(sum / period);
    }
    
    // Pad the beginning with NaN values to match input size
    std::vector<double> result(prices.size(), std::numeric_limits<double>::quiet_NaN());
    std::copy(sma.begin(), sma.end(), result.begin() + period - 1);
    
    return result;
}

void TechnicalAnalysis::setFifSMA(const double& value) {
    indicators.fiftySMA.push_back(value);
}

void TechnicalAnalysis::setHundSMA(const double& value) {
    indicators.hundredSMA.push_back(value);
}

void TechnicalAnalysis::setHundFifSMA(const double& value) {
    indicators.hundFifSMA.push_back(value);
}

void TechnicalAnalysis::setTwoHundSMA(const double& value) {
    indicators.twoHundSMA.push_back(value);
}

void TechnicalAnalysis::setFifEMA(const double& value) {
    indicators.fiftyEMA.push_back(value);
}

void TechnicalAnalysis::setHundEMA(const double& value) {
    indicators.hundredEMA.push_back(value);
}

void TechnicalAnalysis::setHundFifEMA(const double& value) {
    indicators.hundFifEMA.push_back(value);
}

void TechnicalAnalysis::setTwoHundEMA(const double& value) {
    indicators.twoHundEMA.push_back(value);
}

void TechnicalAnalysis::setRSI(const double& value) {
    indicators.RSI.push_back(value);
}

void TechnicalAnalysis::setStoch(const double& value) {
    indicators.stochRSI.push_back(value);
}

void TechnicalAnalysis::setMACD(const double& value) {
    indicators.MACD.push_back(value);
}

void TechnicalAnalysis::setSignal(const double& value) {
    indicators.MACD_Signal.push_back(value);
}

void TechnicalAnalysis::getRSI(std::vector<double>& vec) const {
    vec = indicators.RSI;
}

void TechnicalAnalysis::getStoch(std::vector<double>& vec) const {
    vec = indicators.stochRSI;
}

void TechnicalAnalysis::getFifSMA(std::vector<double>& vec) const {
    vec = indicators.fiftySMA;
}

void TechnicalAnalysis::getHundSMA(std::vector<double>& vec) const {
    vec = indicators.hundredSMA;
}

void TechnicalAnalysis::getHundFifSMA(std::vector<double>& vec) const {
    vec = indicators.hundFifSMA;
}

void TechnicalAnalysis::getTwoHundSMA(std::vector<double>& vec) const {
    vec = indicators.twoHundSMA;
}

void TechnicalAnalysis::getFifEMA(std::vector<double>& vec) const {
    vec = indicators.fiftyEMA;
}

void TechnicalAnalysis::getHundEMA(std::vector<double>& vec) const {
    vec = indicators.hundredEMA;
}

void TechnicalAnalysis::getHundFifEMA(std::vector<double>& vec) const {
    vec = indicators.hundFifEMA;
}

void TechnicalAnalysis::getTwoHundEMA(std::vector<double>& vec) const {
    vec = indicators.twoHundEMA;
}

void TechnicalAnalysis::getMACD(std::vector<double>& vec) const {
    vec = indicators.MACD;
}

void TechnicalAnalysis::getSignal(std::vector<double>& vec) const {
    vec = indicators.MACD_Signal;
}

void TechnicalAnalysis::calcMACD(JSONdata &HistoricalData) {
    assert(!HistoricalData.isEmpty());

    // Calculate 12-day EMA
    std::vector<double> closePrices;
    HistoricalData.accessClose(closePrices);
    
    if (closePrices.size() < 26) {
        std::cout << std::endl << "NOT ENOUGH DATA FOR MACD CALCULATION";
        return;
    }

    // Calculate 12-day EMA
    std::vector<double> ema12 = calculateEMA(closePrices, 12);
    // Calculate 26-day EMA
    std::vector<double> ema26 = calculateEMA(closePrices, 26);
    
    // Calculate MACD line (12-day EMA - 26-day EMA)
    for (size_t i = 0; i < ema12.size(); ++i) {
        if (i < ema26.size()) {
            setMACD(ema12[i] - ema26[i]);
        }
    }
    
    // Calculate Signal line (9-day EMA of MACD)
    std::vector<double> macdLine;
    getMACD(macdLine);
    std::vector<double> signalLine = calculateEMA(macdLine, 9);
    
    for (const auto& value : signalLine) {
        setSignal(value);
    }
}

std::vector<double> TechnicalAnalysis::calculateEMA(const std::vector<double>& prices, size_t period) const {
    std::vector<double> ema;
    if (prices.size() < period) {
        return ema;
    }
    
    // Calculate first EMA using SMA
    double sum = 0.0;
    for (size_t i = 0; i < period; ++i) {
        sum += prices[i];
    }
    double multiplier = 2.0 / (period + 1);
    ema.push_back(sum / period);
    
    // Calculate remaining EMAs
    for (size_t i = period; i < prices.size(); ++i) {
        double currentEMA = (prices[i] - ema.back()) * multiplier + ema.back();
        ema.push_back(currentEMA);
    }
    
    // Pad the beginning with NaN values to match input size
    std::vector<double> result(prices.size(), std::numeric_limits<double>::quiet_NaN());
    std::copy(ema.begin(), ema.end(), result.begin() + period - 1);
    
    return result;
}