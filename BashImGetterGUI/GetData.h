#include <Windows.h>	

#include <string> 

#include "curl\curl.h" 
#include "Parser.h"

class GetData{
public:
	std::vector<std::string> GetDataFromUrl(std::string url, const MapHtmlCode &m);

	std::vector<std::string> resultQuote;

//private:
	//string& getString();

	//size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);


};