

#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "curl.h"

size_t write_data( char *ptr, size_t size, size_t nmemb, FILE* data)
{
    return fwrite(ptr, size, nmemb, data);
}


VOID getData(wchar_t url){

	 // Открываем файл для тела
 
    std::FILE *bodyfile = 0;
    errno_t err; 
    err =  fopen_s(&bodyfile, "body.txt", "w");
    if (err !=0) {
		std::perror("Error");
		std::cin.get();
		std::exit(1);
	}
    // Выполняем  запрос
 
    CURL *curl_handle = curl_easy_init();
 
    if(curl_handle)
        {
            curl_easy_setopt(curl_handle, CURLOPT_URL, "http://bash.im");
 
            // сохраняем тело  
            curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
            curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
           
            CURLcode res = curl_easy_perform(curl_handle);
            if(res != CURLE_OK)
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl_handle);
        }
 
    puts("\nDone!");
    return 0;


}




//Test runner
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int){
	return 0;
}