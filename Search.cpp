#include "Search.h"

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

vector<SearchResult> Search::getResults() {
	return this->results;
}

vector<SearchResult> Search::search(string fragment) {
	string url = string(AVA_ENDPOINT_URL) + "function=SYMBOL_SEARCH&keywords=" + fragment + "&apikey=" + string(AVA_ENDPOINT_ACCESS_KEY);
		
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
	Json::Value jsonData;
	ss >> jsonData;

    if(!this->results.empty()) { // if results is already populated then clear it before repopulating with new results
		this->results.clear();
	}
	
	for(unsigned int i = 0;i < jsonData["bestMatches"].size();i++) {
		string temp;
		SearchResult tempResult;
		
		temp = getString(jsonData["bestMatches"][i]["1. symbol"]);
		tempResult.ticker = temp;
			
		temp = getString(jsonData["bestMatches"][i]["2. name"]);
		tempResult.name = temp;
		
		temp = getString(jsonData["bestMatches"][i]["3. type"]);
		tempResult.type = temp;
		
		temp = getString(jsonData["bestMatches"][i]["4. region"]);
		tempResult.region = temp;
		
		temp = getString(jsonData["bestMatches"][i]["8. currency"]);
		tempResult.currency = temp;
		
		temp = getString(jsonData["bestMatches"][i]["9. matchScore"]);
		tempResult.matchScore = temp;
		
		this->results.push_back(tempResult);
	}
	
	return this->results;
}
