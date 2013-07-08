

#include <vector>
#include <Windows.h>

#include <regex>
#include <string>


#include "MapHtmlCode.h"


class Parser{

public:

	//run func to Parse
	//this func recive string getting from url (getString())
	std::vector<std::string> doParse(std::string& s, MapHtmlCode map);

	int getMaxLineLength();

	std::string getRegexQuote();

	std::string getHtmlSpecSymbolsRegexByName();
	std::string getHtmlSpecSymbolsRegexByCode();

private:
	void replaceAll(std::string& str, const std::string& from, const std::string& to);

	std::string Parser::replace(std::string &resultLine, const std::string &source, const std::string &dest);

};