#include <Windows.h>	

#include <string> 

#include "curl\curl.h" 
#include "Parser.h"

class GetData{
public:
	vector<std::string> GetDataFromUrl(std::string url);

	vector<std::string> resultQuote;

//private:
	//string& getString();

	//size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);


};