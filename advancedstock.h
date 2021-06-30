#ifndef ADVANCEDSTOCK_H
#define ADVANCEDSTOCK_H

#include "Stock.h"
#include <vector>
#include <cstdlib>
#include <numeric>
#include <math.h>

class AdvancedStock : public Stock{
//Extends the stock class to have advanced
//analytics calculated from pulled data
//
private:

    double VWAP;
    double RSI;
    double Volatility;
    void CalculateVWAP();
    void CalculateRSI();
    void CalculateVolatility();
    void calculateAdvancedAnalytics();
public:
    AdvancedStock();
    AdvancedStock(std::string ticker);
    double getVWAP();
    double getRSI();
    double getVolatility();
};

#endif // ADVANCEDSTOCK_H
