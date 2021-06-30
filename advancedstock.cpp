#include "advancedstock.h"

AdvancedStock::AdvancedStock():Stock(){}
AdvancedStock::AdvancedStock(std::string ticker): Stock(ticker){
    calculateAdvancedAnalytics();
}

void AdvancedStock::CalculateVWAP(){
     //access historic price and volume of the stock
     std::vector<double> price1m = this->getHistPrice("1m");
     std::vector<double> volume1m = this->getHistVolume("1m");

     double sumVolume = 0;
     for(std::vector<double>::iterator it = volume1m.begin(); it != volume1m.end(); ++it){
         sumVolume += *it;
     }

     double PriceVolSum = 0;
     for(unsigned int i = 0; i < volume1m.size(); i++){
         PriceVolSum += volume1m[i]*price1m[i];
     }

     VWAP = PriceVolSum/sumVolume;
 }
void AdvancedStock::CalculateRSI(){
    //access the historic price
    std::vector<double> price1m = this->getHistChange("1m");

    double sumGains = 0;
    double SumLosses = 0;
    for(std::vector<double>::iterator it = price1m.begin(); it != price1m.end(); ++it){
        if ((*it) > 0){
            sumGains += *it;
        }
        else{
            SumLosses += *it;
        }
    }
    double RS = sumGains/abs(SumLosses);
    RSI = 100 - (100/(1+RS));
 }
void AdvancedStock::CalculateVolatility(){
    //access the historic price of stock and create interday return vector
    std::vector<double> price1m = this->getHistPrice("1m");
    std::vector<double> interdayReturn(price1m.size() - 1);

    for(unsigned int i = 0; i < interdayReturn.size(); i++){
        interdayReturn[i] = (price1m[i+1]/price1m[i]) - 1;
    }

    double sum = std::accumulate(interdayReturn.begin(), interdayReturn.end(), 0.0);
    double mean = sum / interdayReturn.size();

    double sq_sum = std::inner_product(interdayReturn.begin(), interdayReturn.end(), interdayReturn.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / interdayReturn.size() - mean * mean);

    Volatility = std::sqrt(252)*stdev;  //this is an annualized volatility
}
void AdvancedStock::calculateAdvancedAnalytics(){
    CalculateVWAP();
    CalculateRSI();
    CalculateVolatility();
}
double AdvancedStock::getVWAP(){
    return VWAP;
}
double AdvancedStock::getRSI(){
    return RSI;
}
double AdvancedStock::getVolatility(){
    return Volatility;
}
