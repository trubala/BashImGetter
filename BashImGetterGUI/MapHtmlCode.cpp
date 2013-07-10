
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



bool MapHtmlCode::test_getViewByName(string key){
	getViewByName(key);
	return true;
}

string MapHtmlCode::getViewByName(string key){

	wchar_t utfView;
	string view;

	map<string, string>::iterator iter;
	iter = view_.find(key);

	string code;
	if(iter != view_.end())
		code = iter->second;
	else
		return view;

	regex e("&#(\\w+);");
	smatch matchCode;
	if(regex_match(code, matchCode, e)){

		int iCode = atoi(matchCode[1].str().c_str());
		utfView = iCode;

		char ch[20];
		char DefChar = ' ';
		wchar_t f[20];
		wcscpy(f, (const wchar_t *)&utfView);
		wcscpy(f + 1, L"\0");
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)f, -1, ch, 20, &DefChar, NULL);
		view = ch;

	}

	return view;


}


string MapHtmlCode::getViewByCode(string key){
	wchar_t utfView;
	string view;
	if(!key.empty()){
		int iCode = atoi(key.c_str());
		utfView = iCode;

		char ch[20];
		char DefChar = ' ';
		wchar_t f[20];
		wcscpy(f, (const wchar_t *)&utfView);
		wcscpy(f + 1, L"\0");
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)f, -1, ch, 20, &DefChar, NULL);
		view = ch;
	}
	return view;
}


string MapHtmlCode::getNameCodeRegex(){

	string e (".*?(&\\w+;)(&.*;)");
	return e;

}

bool MapHtmlCode::loadUpFromFile(string fileName){
	ifstream inFile;
	string ansiLine;

	if(fileName.empty())
		return false;

	//wchar_t *ff = L"\u00a1";

	inFile.open(fileName);
	if(inFile.is_open()){
		while(inFile.good()){
			getline(inFile, ansiLine);
			smatch matchNameAndCode;

			regex e (getNameCodeRegex());
			if(regex_match(ansiLine, matchNameAndCode, e)){
				string key = matchNameAndCode[1].str().c_str();
				string value = matchNameAndCode[2].str().c_str();
				view_.insert(std::pair<string, string>(key, value));
			}

		}

	}else
		return false;

	return true;
}