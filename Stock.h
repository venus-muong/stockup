#pragma once
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <memory>
#include <sstream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <vector>
#include <time.h>
#include <stdio.h>

using namespace std;

// using sandbox.iexapis.com (opposed to cloud.iexapis.com) allows us to make unlimited pulls (cloud has a limit to the number of pull requests), but the data is shuffled (not actual)
#define IEX_ENDPOINT_URL "https://sandbox.iexapis.com/stable/"
#define IEX_ENDPOINT_ACCESS_KEY "Tpk_c8897b1c65f241558f5d4d5477241552"

// Define number of data entries that represent certain time periods (Stock exchange doesn't run on weekends so 1 month = ~23 days rather than 30)
const int ONE_MONTH_DATASET = 23;
const int SIX_MONTH_DATASET = 129;
const int ONE_YEAR_DATASET = 253;

class Stock {
private:
	string name; // Company name
	string ticker; // Ticker symbol

	// Current Items:	
	double currPrice;
	double currVolume;
	double currChange;
	double currPercentChange;
	time_t currTimestamp; // marks time of last update
	
	// Historic Items:
	vector<double> histPrice;
	vector<double> histVolume;
	vector<double> histChange;
	vector<double> histPercentChange;
	vector<string> date;
	
	// Statistics:
	double high52;
	double low52;
public:
	Stock() { }
	Stock(string ticker) {
		this->ticker = ticker;
		this->currTimestamp = 0;
		this->getQuote();
		this->updateHistory();
	}
	~Stock() {}

	// Endpoint Access:
	bool getQuote(); // Update current items (15min increment); return true if values were updated
	bool updateHistory(); // Update historic items (daily); return true if values were updated

	// General:
	bool timestampCheck(); // compare curr time to timestamp
	bool dateCheck(); // compare curr date to last stored date
	
	string getName();
	string getTicker();
	void setTicker(string ticker);
	
	double getCurrPrice();
	double getCurrVolume();
	double getCurrChange();
	double getCurrPercentChange();
	time_t getTimestamp();

	vector<double> getHistPrice(string period);
	vector<double> getHistVolume(string period);
	vector<double> getHistChange(string period);
	vector<double> getHistPercentChange(string period);
	vector<string> getDates(string period);

	double getHigh52();
	double getLow52();
};
