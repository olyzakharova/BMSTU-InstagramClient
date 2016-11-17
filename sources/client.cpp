#include "instagram/client.hpp"
#include <string>
#include <curl/curl.h>
#include <iostream>
#include "instagram/json.hpp"
#include <boost/property_tree/json_parser.hpp>


using namespace std;

namespace Instagram
{

    using json = nlohmann::json;

    size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
       {
                 string* buffer = (string*)userp;
                 size_t realsize = size * nmemb;
                 buffer->append((char*)contents, realsize);
                 return realsize;
       }

    auto InstagramClient::check_connection()-> bool
        {

                 CURL *curl = curl_easy_init();
                 string json_;
                 
                 if (curl)
        {

            CURLcode res;
            string token = "4079059384.39f3c6e.29a442eca7f54865a92e071db07cd987";
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl,CURLOPT_WRITEDATA, &json_);
            curl_easy_setopt(curl, CURLOPT_URL, (string("https://api.instagram.com/v1/users/self/?access_token=")+token).c_str());
            res = curl_easy_perform(curl);
			
            if (res == CURLE_OK && json_ != "")
                {
                    boost::property_tree::ptree pt;
                    stringstream ss(json_);
                    boost::property_tree::read_json(ss,pt);
                    boost::property_tree::write_json(cout, pt);
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




    auto InstagramClient::get_most_recent_media()->string
    {
		CURL *curl = curl_easy_init();
		string json_;
		if (curl)
		{
			CURLcode res;
			curl_easy_setopt(curl, CURLOPT_URL, "https://api.instagram.com/v1/users/self/media/recent/?access_token=4079059384.39f3c6e.29a442eca7f54865a92e071db07cd987");
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_callback);
			curl_easy_setopt(curl,CURLOPT_WRITEDATA, &json_);
                        res = curl_easy_perform(curl);
			
                        if (res == CURLE_OK && json_ != "")
            {
				json link =(json::parse(json_))["data"][0]["link"];
				
                                if(link.is_null())
                                   throw std::runtime_error("no link member");
				
                                string str = link.dump(4);
				cout << "link: " << str << endl;
                                curl_easy_cleanup(curl);
				return str;

            }

            else
            {
                curl_easy_cleanup(curl);
                return "vse ochen ploho :c";
            }

		}
    }

}
