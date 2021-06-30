#include "watchlist.h"

watchlist::watchlist(){
    std::string line;
    ifstream myfile (fileName);
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {
          Tickers.push_back(line);
        }
        myfile.close();
      }
      else cout << "Unable to open file";
}
watchlist::~watchlist(){

}
std::vector<std::string> watchlist::GetTickers(){
    return Tickers;
}

void watchlist::writeOutWatchlist(std::vector<AdvancedStock> &m_watchList){
      ofstream myfile (fileName);
      if (myfile.is_open())
      {
          std::vector<AdvancedStock>::iterator it;
          for (it = m_watchList.begin() ; it != m_watchList.end(); ++it){
              myfile << (*it).getTicker() << "\n";
          }
        myfile.close();
      }
      else cout << "Unable to open file";
}
