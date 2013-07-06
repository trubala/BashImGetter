
#include "stdafx.h"
#include "curl\curl.h" 
#include "GetData.h"
#include <clocale>
#include <cwchar>


using namespace std;

//объ€вл€ем буфер, дл€ хранени€ возможной ошибки, размер определ€етс€ в самой библиотеке
static char errorBuffer[CURL_ERROR_SIZE];

//объ€вл€ем буфер принимаемых данных
static string buffer;

// расширенна€ строка дл€ конверсии буфера
wstring wbuffer;

//функци€ обратного вызова
static int writer(char *data, size_t size, size_t nmemb, string *buffer)

{
  //переменна€ - результат, по умолчанию нулева€
  int result = 0;
  //провер€ем буфер
  if (buffer != NULL)  {
    //добавл€ем к буферу строки из data, в количестве nmemb
    buffer->append(data, size * nmemb);
    //вычисл€ем объем прин€тых данных
    result = size * nmemb;
  }
  //возвращаем результат
  return result;
}


vector<std::string> GetData::GetDataFromUrl(std::string url){ 
	std::setlocale(LC_ALL, "Russian_Russia.1251");
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
        	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
       		 //указываем куда записывать принимаемые данные
        	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		//запускаем выполнение задачи
		result = curl_easy_perform(curl); 
		// вариант конверсии buffer to wstring
		for (long int i=0; i<buffer.size(); ++i) {
			wbuffer[i] = std::btowc(buffer[i]);
			if (wbuffer[i] == WEOF)
				MessageBoxA(0, "Error conversion", "Error", 0);
		}
		wbuffer.push_back('\0');
		Parser parser;
		resultQuote = parser.doParse(wbuffer);
		
		//провер€ем успешность выполнени€ операции
		if(result != CURLE_OK) 
			MessageBoxA(0, "Error: get url is bad", "ERROR", 0) ; 

		//завершаем сессию
		curl_easy_cleanup(curl); 

	} 


	return resultQuote;
}


