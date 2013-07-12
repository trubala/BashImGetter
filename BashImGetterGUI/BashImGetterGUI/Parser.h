
#pragma once

#include <vector>
#include <Windows.h>
#include <regex>
#include <string>


#include "MapHtmlCode.h"


class Parser{

public:

	std::vector<std::string> doParse(std::string& lineToParse, MapHtmlCode& map);

	int getMaxLineLength();

	std::string getRegexGetQuote();

	std::string getHtmlSpecSymbolsRegexByName();

	std::string getHtmlSpecSymbolsRegexByCode();

private:

	void replaceAll(std::string& str, const std::string& from, const std::string& to);

};