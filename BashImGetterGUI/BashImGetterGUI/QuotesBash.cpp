
#include "stdafx.h"
#include "QuotesBash.h"
#include "curl\curl.h" 
#include <iostream>
#include <fstream>

using namespace std;


static char errorBuffer[CURL_ERROR_SIZE];
static string buffer;

static int appendLine(const char *data, const size_t size, const size_t nmemb, string *buffer) {

	if (buffer != NULL) {
		buffer->append(data, size * nmemb);
	}
	return size * nmemb;
}

vector<std::string>QuotesBash::getQuotesFromUrl(const std::string url, MapHtmlCode &mapHtmlCodes) { 
	CURL *curl; 
	CURLcode result; 
	curl = curl_easy_init(); 
	if(curl) { 
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); 
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); 
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, appendLine);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		result = curl_easy_perform(curl);

		if(result != CURLE_OK) {
			MessageBoxA(0, "Error: get url is bad. See log_error.txt", "ERROR", 0);
			ofstream fw("log_error.txt", ios::out | ios::trunc, _SH_DENYRW);	
			if (!fw) {
				MessageBoxA(0, "Error open log_error.txt", "ERROR", 0);				
			}
			fw << errorBuffer << endl;
			fw.close();
		}else{

			Parser parser;
			quotes = parser.doParse(buffer, mapHtmlCodes);
		}

		curl_easy_cleanup(curl); 
	} 
	return quotes;
}


