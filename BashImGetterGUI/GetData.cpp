//
//#include "stdafx.h"
//
//#include "GetData.h"
//
//
//
//using namespace std;

//string& getString() { 
//	static std::string s; 
//	return s; 
//} 
//
//
//size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) 
//{ 
//	size_t totalSize = nmemb * size; 
//
//	char *str = new char[totalSize + 1]; 
//	memcpy(str, ptr, totalSize); 
//
//	str[totalSize] = '\0'; 
//
//	std::string& result = getString(); 
//	result += str; 
//
//	delete [] str;
//
//	return totalSize; 
//} 
//
//
//vector<std::string> GetData::GetDataFromUrl(std::string url){ 
//	CURL *curl; 
//	CURLcode res; 
//
//	curl = curl_easy_init(); 
//	if(curl) { 
//		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); 
//		/* example.com is redirected, so we tell libcurl to follow redirection */ 
//		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); 
//
//		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 
//
//
//
//		/* Perform the request, res will get the return code */ 
//		res = curl_easy_perform(curl); 
//
//		Parser parser;
//		resultQuote = parser.doParse(getString());
//
//
//		/* Check for errors */ 
//		if(res != CURLE_OK) 
//			MessageBoxA(0, "Error: get url is bad", "ERROR", 0) ; 
//
//		/* always cleanup */ 
//		curl_easy_cleanup(curl); 
//
//	} 
//
//
//	return resultQuote;
//}


#include "stdafx.h"

#include "GetData.h"


using namespace std;

//объ€вл€ем буфер, дл€ хранени€ возможной ошибки, размер определ€етс€ в самой библиотеке

static char errorBuffer[CURL_ERROR_SIZE];

//объ€вл€ем буфер принимаемых данных

static string buffer;

//функци€ обратного вызова

static int writer(char *data, size_t size, size_t nmemb, string *buffer)

{

  //переменна€ - результат, по умолчанию нулева€

  int result = 0;

  //провер€ем буфер

  if (buffer != NULL)

  {

    //добавл€ем к буферу строки из data, в количестве nmemb

    buffer->append(data, size * nmemb);

    //вычисл€ем объем прин€тых данных

    result = size * nmemb;

  }

  //возвращаем результат

  return result;

}


vector<std::string> GetData::GetDataFromUrl(std::string url){ 
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
		Parser parser;
		resultQuote = parser.doParse(buffer);

		//провер€ем успешность выполнени€ операции
		if(result != CURLE_OK) 
			MessageBoxA(0, "Error: get url is bad", "ERROR", 0) ; 

		//завершаем сессию
		curl_easy_cleanup(curl); 

	} 


	return resultQuote;
}


