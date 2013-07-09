
#include "stdafx.h"
#include "GetData.h"
#include "curl\curl.h" 
#include <iostream>
#include <fstream>

using namespace std;
//объ€вл€ем буфер, дл€ хранени€ возможной ошибки, размер определ€етс€ в самой библиотеке
static char errorBuffer[CURL_ERROR_SIZE];
//объ€вл€ем буфер принимаемых данных
static string buffer;

//функци€ обратного вызова
static int writestr(char *data, size_t size, size_t nmemb, string *buffer) {
  //переменна€ - результат, по умолчанию нулева€
  int result = 0;
  //провер€ем буфер
  if (buffer != NULL) {
    //добавл€ем к буферу строки из data, в количестве nmemb
    buffer->append(data, size * nmemb);
    //вычисл€ем объем прин€тых данных
    result = size * nmemb;
  }
  //возвращаем результат
  return result;
}

vector<std::string> GetData::GetDataFromUrl(std::string url, const MapHtmlCode &m) { 
	CURL *curl; 
	CURLcode result; 
	curl = curl_easy_init(); 
	if(curl) { 
		//определ€ем, куда выводить ошибки
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		//задаем опцию - получить страницу по адресу 
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); 
		// переадресаци€, если необходимо
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); 
		//указываем функцию обратного вызова дл€ записи получаемых данных
        	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writestr);
       		 //указываем куда записывать принимаемые данные
        	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		//запускаем выполнение задачи
		result = curl_easy_perform(curl);
		//провер€ем успешность выполнени€ операции
		if(result != CURLE_OK) {
			MessageBoxA(0, "Error: get url is bad. See log_error.txt", "ERROR", 0);
			ofstream fw("log_error.txt", ios::out | ios::trunc, _SH_DENYRW);	
        		// обработка ошибки открыти€ файла
				if (!fw) {
					MessageBoxA(0, "Error open log_error.txt", "ERROR", 0);				
					}
				fw << errorBuffer << endl;
		}
		Parser parser;
		resultQuote = parser.doParse(buffer, m);
		//завершаем сессию
		curl_easy_cleanup(curl); 
	} 
	return resultQuote;
}

		
	