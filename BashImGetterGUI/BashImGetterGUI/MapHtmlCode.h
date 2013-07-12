

#pragma once


#include <string>
#include <map>

class MapHtmlCode{


public:
	std::string getSymbolByName(std::string key);

	std::string getSymbolByCode(std::string key);

	bool loadUpFromFile(std::string fileName);

private:
	std::map<std::string, std::string> mapCodesSymbols_;

	std::string getExpressionRegex();

	static const int bufferSize_ = 20;


};