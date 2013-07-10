
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

string Parser::getRegexQuote(){
	return ".*<div class=\"text\">(.*)</div>";
}


string Parser::getHtmlSpecSymbolsRegexByName(){
	//return ".*?(&\\w+;)|(&.*;).*?";
	return ".*?(&\\w+;).*?";
}

string Parser::getHtmlSpecSymbolsRegexByCode(){
	return ".*?(&.*;).*?";
}


string Parser::replace(std::string &resultLine, const std::string &source, const std::string &dest){
	unsigned index = resultLine.find(source.c_str());
	if(index != std::string::npos){
		unsigned len = source.length();
		resultLine.replace(index, index + len, dest);

	}
	return resultLine;
}

vector<std::string> Parser::doParse(string& s, MapHtmlCode map){
	vector<std::string> result;
	vector<std::string> lineByLineStr;

	//----replace line by line---- [begin]
	unsigned int pos = 0;

	bool oneMatch = false;
	while(s.length() > 0){
		pos = s.find("\n");
		if(pos != -1){
			oneMatch = true;
			string subString = s.substr(0, pos);
			lineByLineStr.push_back(subString);
			s = s.substr(pos + 1);
		}else{
			if(!oneMatch)
				MessageBoxA(0, "Getted content don't have '\n' symbols", "Error Parse", 0);
			break;
		}
	}
	//----replace line by line---- [end]

	//-----get quote in bash.im-----[begin]
	regex e (getRegexQuote());

	for(unsigned i = 0; i < lineByLineStr.size(); ++i){
		string line = lineByLineStr.at(i);
		std::smatch match;



		if (std::regex_match(line, match, e))
		{
			string resultMatch = match[1].str().c_str();

			regex findSpecSymbols (getHtmlSpecSymbolsRegexByName());
			smatch matchSpecSymbols;
			string symbol;

			if(regex_match(resultMatch, matchSpecSymbols, findSpecSymbols)){

				
				if(!matchSpecSymbols[1].str().empty()){
					//finded name, example = &frac34;
					symbol = map.getViewByName(matchSpecSymbols[1].str());
					//replace
					resultMatch = replace(resultMatch, matchSpecSymbols[1].str(), symbol);

				}
			}

			findSpecSymbols  = getHtmlSpecSymbolsRegexByCode();

			if(regex_match(resultMatch, matchSpecSymbols, findSpecSymbols)){
				if(!matchSpecSymbols[1].str().empty()){
					//finded name, example = &#402;
					symbol = map.getViewByCode(matchSpecSymbols[1].str());
					//replace
					resultMatch = replace(resultMatch, matchSpecSymbols[1].str(), symbol);
				}
			}

			replaceAll(resultMatch, "<br>", "\r\n");
			replaceAll(resultMatch, "<br />", "\r\n");
			/*
			replaceAll(resultMatch, "&quot;", "\"");
			replaceAll(resultMatch, "&lt;", "<");
			replaceAll(resultMatch, "&gt;", ">");
			replaceAll(resultMatch, "&#039;", "'");*/

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

			result.push_back(resultMatch);
			//MessageBoxA(0, resultMatch.c_str(), "Quote", 0);
		}

	}
	//-----get quote in bash.im-----[end]
	return result;

}


