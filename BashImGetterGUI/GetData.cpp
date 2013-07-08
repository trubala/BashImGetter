
#include "stdafx.h"

#include "GetData.h"


using namespace std;

//��������� �����, ��� �������� ��������� ������, ������ ������������ � ����� ����������

static char errorBuffer[CURL_ERROR_SIZE];

//��������� ����� ����������� ������

static string buffer;

//������� ��������� ������

static int writer(char *data, size_t size, size_t nmemb, string *buffer)

{

  //���������� - ���������, �� ��������� �������

  int result = 0;

  //��������� �����

  if (buffer != NULL)

  {

    //��������� � ������ ������ �� data, � ���������� nmemb

    buffer->append(data, size * nmemb);

    //��������� ����� �������� ������

    result = size * nmemb;

  }

  //���������� ���������

  return result;

}


vector<std::string> GetData::GetDataFromUrl(std::string url, const MapHtmlCode &m){ 
	CURL *curl; 
	CURLcode result; 

	curl = curl_easy_init(); 
	if(curl) { 
		//����������, ���� �������� ������
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		//������ ����� - �������� �������� �� ������ 
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); 
		// �������������, ���� ����������
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); 

		//��������� ������� ��������� ������ ��� ������ ���������� ������
        	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
       		 //��������� ���� ���������� ����������� ������
        	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		//��������� ���������� ������
		result = curl_easy_perform(curl); 

		
		Parser parser;
		resultQuote = parser.doParse(buffer, m);
		

		//��������� ���������� ���������� ��������
		if(result != CURLE_OK) 
			MessageBoxA(0, "Error: get url is bad", "ERROR", 0) ; 

		//��������� ������
		curl_easy_cleanup(curl); 

	} 


	return resultQuote;
}


