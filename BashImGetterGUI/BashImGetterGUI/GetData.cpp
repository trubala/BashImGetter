
#include "stdafx.h"

#include "GetData.h"



using namespace std;

string& getString() { 
	static std::string s; 
	return s; 
} 


size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) 
{ 
	size_t totalSize = nmemb * size; 

	char *str = new char[totalSize + 1]; 
	memcpy(str, ptr, totalSize); 

	str[totalSize] = '\0'; 

	std::string& result = getString(); 
	result += str; 

	delete [] str;

	return totalSize; 
} 


vector<std::string> GetData::GetDataFromUrl(std::string url){ 
	CURL *curl; 
	CURLcode res; 

	curl = curl_easy_init(); 
	if(curl) { 
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); 
		/* example.com is redirected, so we tell libcurl to follow redirection */ 
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); 

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 



		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl); 

		Parser parser;
		resultQuote = parser.doParse(getString());


		/* Check for errors */ 
		if(res != CURLE_OK) 
			MessageBoxA(0, "Error: get url is bad", "ERROR", 0) ; 

		/* always cleanup */ 
		curl_easy_cleanup(curl); 

	} 


	return resultQuote;
}

