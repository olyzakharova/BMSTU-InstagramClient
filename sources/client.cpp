#include "instagram/client.hpp"
#include <string>
#include <curl/curl.h>
#include <iostream>


using namespace std;

namespace Instagram
{
	auto InstagramClient::check_connection()-> bool
	{

		CURL *curl = curl_easy_init();
		if (curl)
		{

			CURLcode res;
			string token = "4079059384.39f3c6e.29a442eca7f54865a92e071db07cd987";
			curl_easy_setopt(curl, CURLOPT_URL, (string("https://api.instagram.com/v1/users/self/?access_token=")+token).c_str())
			res = curl_easy_perform(curl);
			if (res == CURLE_OK)
			{
				cout << "authentication is successful" << endl;
				return true;
			}

			if (res != CURLE_OK)
			{ 
				cout << "your access token isn't correct" << endl;
				return false;
			}
			curl_easy_cleanup(curl);
		}

	}




	/*auto InstagramClient::get_most_recent_media() -> void
	{
		CURL *curl = curl_easy_init();
		if (curl)
		{
			CURLcode res;
			curl_easy_setopt(curl, CURLOPT_URL, "https://api.instagram.com/v1/users/self/media/recent/?access_token=4079059384.39f3c6e.29a442eca7f54865a92e071db07cd987");
			res = curl_easy_perform(curl);
			if (res == CURLE_OK)
			{
				cout << "tadaaaaa!" << endl;
				return true;
			}

			curl_easy_cleanup(curl);

		}
	}*/
}
