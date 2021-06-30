#include "Stock.h"

static std::size_t httpRequestToStringCallback(const char* in,
                                               std::size_t size,
                                               std::size_t num,
                                               std::string* out) {
	const std::size_t totalBytes(size * num);
	out->append(in, totalBytes);
	return totalBytes;
}

static std::string getString(const Json::Value& v) {
	if (!v) {
		return "";
	} else {
		return v.asString();
	}
}

// Update current items (in 15 min increments)
bool Stock::getQuote() {
	if(this->timestampCheck()) { // update quote only if last pull was > 15 min ago
		//cout << "Getting quote..." << endl;
		string url = string(IEX_ENDPOINT_URL) + "stock/" + this->ticker + "/quote?token=" + string(IEX_ENDPOINT_ACCESS_KEY);
		
		CURL* curl = curl_easy_init();

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		long int httpCode(0);
		
		unique_ptr<string> httpData(new std::string);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpRequestToStringCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
		curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		curl_easy_cleanup(curl);
		
		std::stringstream ss;
		ss.str(*httpData);
		if(*httpData == "Unknown symbol") { throw *httpData;}
		Json::Value jsonData;
		ss >> jsonData;
		
		string temp;
		if(this->name.empty()) {
			this->name = getString(jsonData["companyName"]);
		}
		temp = getString(jsonData["latestPrice"]);
		if(temp != "") { this->currPrice = stod(temp); } // null check
		else { this->currPrice = 0; }
		
		temp = getString(jsonData["latestVolume"]);
		if(temp != "") { this->currVolume = stod(temp); } // null check
		else { this->currVolume = 0; }
	
		temp = getString(jsonData["change"]);
		if(temp != "") { this->currChange = stod(temp); } // null check
		else { this->currChange = 0; }
		
		temp = getString(jsonData["changePercent"]);
		if(temp != "") { this->currPercentChange = stod(temp); } // null check
		else { this->currPercentChange = 0; }
		
		
		temp = getString(jsonData["week52High"]);
		if(temp != "") { this->high52 = stod(temp); } // null check
		else { this->high52 = 0; }
		
		temp = getString(jsonData["week52Low"]);
		if(temp != "") { this->low52 = stod(temp); } // null check
		else { this->low52 = 0; }
		
		return true;
	}
	return false;
}

// Update historic items (daily)
bool Stock::updateHistory() {
	if(this->dateCheck()) { // update historic data if missing more than 1 day of data
		//cout << "Getting history..." << endl;
		string url = string(IEX_ENDPOINT_URL) + "stock/" + this->ticker + "/chart/5y?token=" + string(IEX_ENDPOINT_ACCESS_KEY);
		
		CURL* curl = curl_easy_init();

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		long int httpCode(0);
		
		unique_ptr<string> httpData(new std::string);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, httpRequestToStringCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
		curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		curl_easy_cleanup(curl);
		
		std::stringstream ss;
		ss.str(*httpData);
		if(*httpData == "Unknown symbol") { throw *httpData;}
		Json::Value jsonData;
		ss >> jsonData;
		
		if(!(this->histPrice.empty())) { // if histPrice is populated (all hist values populated) then clear it before repopulating
			this->histPrice.clear();
			this->histVolume.clear();
			this->histChange.clear();
			this->histPercentChange.clear();
			this->date.clear();
		}
		
		for(unsigned int i = 0;i < jsonData.size();i++) {
			string temp;
			temp = getString(jsonData[i]["close"]);
			if(temp != "") { this->histPrice.push_back(stod(temp)); } // null check
			else { this->histPrice.push_back(0); }
			
			temp = getString(jsonData[i]["volume"]);
			if(temp != "") { this->histVolume.push_back(stod(temp)); } // null check
			else { this->histVolume.push_back(0); }
		
			temp = getString(jsonData[i]["change"]);
			if(temp != "") { this->histChange.push_back(stod(temp)); } // null check
			else { this->histChange.push_back(0); }
			
			temp = getString(jsonData[i]["changePercent"]);
			if(temp != "") { this->histPercentChange.push_back(stod(temp)); } // null check
			else { this->histPercentChange.push_back(0); }
			
			this->date.push_back(getString(jsonData[i]["date"]));
		}
		return true;
	}
	return false;
}


// compare curr time to timestamp (if > 15 min ago, update timestamp and return true)
bool Stock::timestampCheck() {
	time_t currTime = time(nullptr);
	if(this->currTimestamp == 0 || (difftime(currTime,this->currTimestamp) >= (15*60))) {
		this->currTimestamp = currTime;
		return true;
	}
	return false;
}

// compare curr date to last stored date
bool Stock::dateCheck() {
	if(this->date.empty()) {
		return true;
	}
	time_t currTime = time(nullptr);
	struct tm* tm = localtime(&currTime);
	vector<string>::iterator recentDate = this->date.end()-1;
	
	int recentYear, recentMonth, recentDay;
	sscanf((*recentDate).c_str(), "%d-%d-%d", &recentYear, &recentMonth, &recentDay);

	if(((tm->tm_year+1900) > recentYear) || tm->tm_mon > recentMonth || tm->tm_mday > (recentDay+1)) {
		return true;
	}
	return false;
}

string Stock::getName() {
	return this->name;
}
	
string Stock::getTicker() {
	return this->ticker;
}

void Stock::setTicker(string ticker) {
	if(this->ticker.empty()) {
		this->ticker = ticker;
		this->currTimestamp = 0;
		this->getQuote();
		this->updateHistory();
	}
	else { 
		string error = "Ticker already defined";
		throw error;
	}
}
	
double Stock::getCurrPrice() {
	if(this->ticker.empty()) {
		string error = "Ticker not defined";
		throw error;
	}
	this->getQuote();
	return this->currPrice;
}

double Stock::getCurrVolume() {
	if(this->ticker.empty()) { 
		string error = "Ticker not defined";
		throw error;
	}
	this->getQuote();
	return this->currVolume;
}

double Stock::getCurrChange() {
	if(this->ticker.empty()) {	
		string error = "Ticker not defined";
		throw error;
	}
	this->getQuote();
	return this->currChange;
}

double Stock::getCurrPercentChange() {
	if(this->ticker.empty()) { 
		string error = "Ticker not defined";
		throw error;
	}
	this->getQuote();
	return this->currPercentChange;
}

time_t Stock::getTimestamp() {
	if(this->ticker.empty()) { 
		string error = "Ticker not defined";
		throw error;
	}
	return this->currTimestamp;
}

vector<double> Stock::getHistPrice(string period) {
	if(this->ticker.empty()) { 
		string error = "Ticker not defined";
		throw error;
	}
	this->updateHistory();
	
	vector<double>::iterator first;
	vector<double>::iterator last = this->histPrice.end();
	
	if(period == "1m") { first = this->histPrice.end()-ONE_MONTH_DATASET; } // size of vector = 23
	else if(period == "6m") { first = this->histPrice.end()-SIX_MONTH_DATASET; } // size of vector = 129
	else if(period == "1y") { first = this->histPrice.end()-ONE_YEAR_DATASET; } // size of vector = 253
	else if(period == "5y") { return this->histPrice; }  // size of vector = 1259
	else { 
		string error = "Not a valid time period!";
		throw error; 
	}
	
	vector<double> histPricePeriod(first,last);
	return histPricePeriod;
}

vector<double> Stock::getHistVolume(string period) {
	if(this->ticker.empty()) { 
		string error = "Ticker not defined";
		throw error;
	}
	this->updateHistory();
	
	vector<double>::iterator first;
	vector<double>::iterator last = this->histVolume.end();
	
	if(period == "1m") { first = this->histVolume.end()-ONE_MONTH_DATASET; } // size of vector = 23
	else if(period == "6m") { first = this->histVolume.end()-SIX_MONTH_DATASET; } // size of vector = 129
	else if(period == "1y") { first = this->histVolume.end()-ONE_YEAR_DATASET; } // size of vector = 253
	else if(period == "5y") { return this->histVolume; } // size of vector = 1259
	else { 
		string error = "Not a valid time period!";
		throw error; 
	}
	
	vector<double> histVolumePeriod(first,last);
	return histVolumePeriod;
}

vector<double> Stock::getHistChange(string period) {
	if(this->ticker.empty()) { 
		string error = "Ticker not defined";
		throw error;
	}
	this->updateHistory();
	
	vector<double>::iterator first;
	vector<double>::iterator last = this->histChange.end();
	
	if(period == "1m") { first = this->histChange.end()-ONE_MONTH_DATASET; } // size of vector = 23
	else if(period == "6m") { first = this->histChange.end()-SIX_MONTH_DATASET; } // size of vector = 129
	else if(period == "1y") { first = this->histChange.end()-ONE_YEAR_DATASET; } // size of vector = 253
	else if(period == "5y") { return this->histChange; } // size of vector = 1259
	else { 
		string error = "Not a valid time period!";
		throw error; 
	}
	
	vector<double> histChangePeriod(first,last);
	return histChangePeriod;
}

vector<double> Stock::getHistPercentChange(string period) {
	if(this->ticker.empty()) { 
		string error = "Ticker not defined";
		throw error;
	}
	this->updateHistory();
	
	vector<double>::iterator first;
	vector<double>::iterator last = this->histPercentChange.end();
	
	if(period == "1m") { first = this->histPercentChange.end()-ONE_MONTH_DATASET; } // size of vector = 23
	else if(period == "6m") { first = this->histPercentChange.end()-SIX_MONTH_DATASET; } // size of vector = 129
	else if(period == "1y") { first = this->histPercentChange.end()-ONE_YEAR_DATASET; } // size of vector = 253
	else if(period == "5y") { return this->histPercentChange; } // size of vector = 1259
	else { 
		string error = "Not a valid time period!";
		throw error; 
	}
	
	vector<double> histPercentChangePeriod(first,last);
	return histPercentChangePeriod;
}

vector<string> Stock::getDates(string period) {
	if(this->ticker.empty()) { 
		string error = "Ticker not defined";
		throw error;
	}
	this->updateHistory();
	
	vector<string>::iterator first;
	vector<string>::iterator last = this->date.end();
	
	if(period == "1m") { first = this->date.end()-ONE_MONTH_DATASET; } // size of vector = 23
	else if(period == "6m") { first = this->date.end()-SIX_MONTH_DATASET; } // size of vector = 129
	else if(period == "1y") { first = this->date.end()-ONE_YEAR_DATASET; } // size of vector = 253
	else if(period == "5y") { return this->date; } // size of vector = 1259
	else { 
		string error = "Not a valid time period!";
		throw error; 
	}
	
	vector<string> datePeriod(first,last);
	return datePeriod;
}

double Stock::getHigh52() {
	if(this->ticker.empty()) { 
		string error = "Ticker not defined";
		throw error;
	}
	this->getQuote();
	return this->high52;
}

double Stock::getLow52() {
	if(this->ticker.empty()) { 
		string error = "Ticker not defined";
		throw error;
	}
	this->getQuote();
	return this->low52;
}
