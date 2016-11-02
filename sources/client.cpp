#include "include/instagram/client.hpp"
#include <string>
#include <curl/curl.h>
#include <iostream>


using namespace std;

namespace Instagram 
{
	auto InstagramClient::check_connection()-> bool
	{
	
			CURL *curl_ = curl_easy_init();
			if (curl_)
			{   
				string token = "access token " + settings_["token"] + "4079059384.39f3c6e.29a442eca7f54865a92e071db07cd987");
				CURLcode res;
				curl_easy_stopt(curl, CURLOPT_URL, ""); // какой адрес ?!
				curl_easy_stopt(curl, CURLOPT_POST, token.c_str()); //  c_str формирует массив строк в стиле си. И возвращает указатель на него.
				res = curl_easy_perform(curl);
				if (res == CURLE_OK)
					{
						cout << "authentication is successful" << endl;
						return true;
					}
				
			    curl_easy_cleanup(curl);
			}
		
	 }
}

