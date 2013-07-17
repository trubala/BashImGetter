#pragma once

#include <Windows.h>	

#include <string> 

#include "Parser.h"

class QuotesBash{
public:
	std::vector<std::string> getQuotesFromUrl(const std::string url, MapHtmlCode &m);

	std::vector<std::string> quotes;

};