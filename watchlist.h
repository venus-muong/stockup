#ifndef WATCHLIST_H
#define WATCHLIST_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <vector>
#include <time.h>
#include <stdio.h>
#include "Stock.h"
#include "advancedstock.h"

#define fileName "SavedWatchList.txt"
class watchlist{
public:
    watchlist();
    ~watchlist();
    std::vector<std::string> GetTickers();
    void writeOutWatchlist(std::vector<AdvancedStock> &m_watchList);

private:
    std::vector<std::string> Tickers;
};

#endif // WATCHLIST_H
