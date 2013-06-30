#include <vector>
#include <Windows.h>

#include <regex>
#include <string>


using namespace std;

const std::string regexGetQuote = ".*<div class=\"text\">(.*)</div>";

class Parser{

public:

	vector<std::string> doParse(string& s);

private:
	void replaceAll(std::string& str, const std::string& from, const std::string& to);

};