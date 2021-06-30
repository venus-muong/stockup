#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <memory>
#include <sstream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <stdio.h>

using namespace std;

// Defining constants for the Alpha Vantage access endpoint
#define AVA_ENDPOINT_URL "https://www.alphavantage.co/query?"
#define AVA_ENDPOINT_ACCESS_KEY "5EEO0UBE5CL7WO68"

struct SearchResult {
	string ticker, name, type, region, currency, matchScore;
};

class Search {
private:
	vector<SearchResult> results;
	
public:
    Search() { }
	~Search() { }
	
	vector<SearchResult> getResults();
	vector<SearchResult> search(string fragment);
};
