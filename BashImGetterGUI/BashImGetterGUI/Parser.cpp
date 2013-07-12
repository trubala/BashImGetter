
#include "stdafx.h"

#include "Parser.h"

using namespace std;

void Parser::replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if(from.empty())
		return;
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}


int Parser::getMaxLineLength(){
	return 80;
}

string Parser::getRegexGetQuote(){
	return ".*<div class=\"text\">(.*)</div>";
}


string Parser::getHtmlSpecSymbolsRegexByName(){
	return ".*?(&\\w+;).*?";
}

string Parser::getHtmlSpecSymbolsRegexByCode(){
	return ".*?(&#.*;).*?";
}

vector<string> Parser::doParse(string& lineToParse, MapHtmlCode& map){
	vector<string> result;
	vector<string> lineByLineStr;
	unsigned pos = 0;

	bool oneMatch = false;
	while(lineToParse.length() > 0){
		pos = lineToParse.find("\n");
		if(pos != string::npos){
			oneMatch = true;
			string subString = lineToParse.substr(0, pos);
			lineByLineStr.push_back(subString);
			lineToParse = lineToParse.substr(pos + 1);
		}else{
			if(!oneMatch)
				MessageBoxA(0, "Getted content don't have '\n' symbols", "Error Parse", 0);
			break;
		}
	}

	regex expression(getRegexGetQuote());

	for(unsigned i = 0; i < lineByLineStr.size(); ++i){
		string line = lineByLineStr.at(i);
		std::smatch match;



		if (std::regex_match(line, match, expression))
		{

			string resultMatch = match[1].str().c_str();

			bool noMatchesByName = false;
			bool noMatchesByCode = false;
			while(noMatchesByName == false && noMatchesByCode == false){
				regex findSpecSymbols (getHtmlSpecSymbolsRegexByName());
				smatch matchSpecSymbols;
				string symbol;

				if(regex_match(resultMatch, matchSpecSymbols, findSpecSymbols)){

					if(!matchSpecSymbols[1].str().empty()){
						//finded name, example = &frac34;
						symbol = map.getSymbolByName(matchSpecSymbols[1].str());
						replaceAll(resultMatch, matchSpecSymbols[1].str(), symbol);

					}

					noMatchesByName = false;

				}else
					noMatchesByName = true;

				findSpecSymbols  = getHtmlSpecSymbolsRegexByCode();

				if(regex_match(resultMatch, matchSpecSymbols, findSpecSymbols)){

					if(!matchSpecSymbols[1].str().empty()){
						//finded name, example = &#402;
						symbol = map.getSymbolByCode(matchSpecSymbols[1].str());
						replaceAll(resultMatch, matchSpecSymbols[1].str(), symbol);
					}
					noMatchesByCode = false;
				}else
					noMatchesByCode = true;

				replaceAll(resultMatch, "<br>", "\r\n");
				replaceAll(resultMatch, "<br />", "\r\n");

				int max = getMaxLineLength();

				if(resultMatch.length() > max){
					int j = max;
					while(j < resultMatch.length()){
						int foundIndex = resultMatch.find(" ", j);
						if(foundIndex != string::npos){
							resultMatch.insert(foundIndex, "\r\n");
							j = foundIndex + max;
						}else
							break;
					}
				}
			}

			result.push_back(resultMatch);
		}

	}

	return result;

}


