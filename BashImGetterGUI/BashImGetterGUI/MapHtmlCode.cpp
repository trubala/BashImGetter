
#include "stdafx.h"

#include "MapHtmlCode.h"

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <regex>
#include <iomanip>
#include <sstream>

using namespace std;

string MapHtmlCode::getSymbolByName(string key){

	wchar_t symbolW;
	string symbolA;

	map<string, string>::iterator iter;
	iter = mapCodesSymbols_.find(key);

	string code;
	if(iter != mapCodesSymbols_.end())
		code = iter->second;
	else
		return symbolA;

	regex expression("&#(\\w+);");
	smatch matchCode;
	if(regex_match(code, matchCode, expression)){

		int iCode = atoi(matchCode[1].str().c_str());
		symbolW = iCode;

		char bufferForSymbolA[bufferSize_];
		char defChar = ' ';
		wchar_t bufferForSymbolW[bufferSize_];
		wcscpy(bufferForSymbolW, (const wchar_t *)&symbolW);
		wcscpy(bufferForSymbolW + 1, L"\0");
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)bufferForSymbolW, -1, bufferForSymbolA, bufferSize_, &defChar, NULL);
		symbolA = bufferForSymbolA;

	}

	return symbolA;

}


string MapHtmlCode::getSymbolByCode(string key){

	wchar_t symbolW;
	string symbolA;
	if(!key.empty()){
		int iCode = atoi(key.c_str());
		symbolW = iCode;

		char bufferForSymbolA[bufferSize_];
		char defChar = ' ';
		wchar_t bufferForSymbolW[bufferSize_];
		wcscpy(bufferForSymbolW, (const wchar_t *)&symbolW);
		wcscpy(bufferForSymbolW + 1, L"\0");
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)bufferForSymbolW, -1, bufferForSymbolA, bufferSize_, &defChar, NULL);
		symbolA = bufferForSymbolA;
	}
	return symbolA;

}


string MapHtmlCode::getExpressionRegex(){

	string expression (".*?(&\\w+;)(&.*;)");
	return expression;

}

bool MapHtmlCode::loadUpFromFile(string fileName){

	ifstream inFile;
	string lineA;

	if(fileName.empty())
		return false;

	inFile.open(fileName);
	if(inFile.is_open()){
		while(inFile.good()){
			getline(inFile, lineA);
			smatch matchNameAndCode;

			regex expression (getExpressionRegex());
			if(regex_match(lineA, matchNameAndCode, expression)){
				string key = matchNameAndCode[1].str().c_str();
				string value = matchNameAndCode[2].str().c_str();
				mapCodesSymbols_.insert(std::pair<string, string>(key, value));
			}

		}

	}else
		return false;

	return true;

}