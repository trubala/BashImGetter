

#pragma once


#include <string>
#include <map>

class MapHtmlCode{


public:
	std::string getViewByName(std::string key);

	std::string getViewByCode(std::string key);

	bool loadUpFromFile(std::string fileName);

	bool test_getViewByName(std::string key);

private:
	std::map<std::string, std::string> view_;

	std::string getNameCodeRegex();

};