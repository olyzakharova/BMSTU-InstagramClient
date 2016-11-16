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


    static string buffer;

    size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
       {
                 size_t realsize = size * nmemb;
                 buffer.append((char*)contents, realsize);
                    return realsize;
       }

    auto InstagramClient::check_connection()-> bool
        {

                 CURL *curl = curl_easy_init();
                 if (curl)
        {

            CURLcode res;
            string token = "4079059384.39f3c6e.29a442eca7f54865a92e071db07cd987";
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_URL, (string("https://api.instagram.com/v1/users/self/?access_token=")+token).c_str());
            buffer.clear();
            res = curl_easy_perform(curl);
            if (res == CURLE_OK)
                {
                    boost::property_tree::ptree pt;
                    stringstream ss(buffer);
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
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,callback);
            curl_easy_setopt(curl,CURLOPT_WRITEDATA, &json_);
            res = curl_easy_perform(curl);
            if (res == CURL_OK && json != "")
            {
                json link =(json::parse(json_))["data"]["link"];
                curl_easy_cleanup(curl);
                return link;

            }

            else
            {
                curl_easy_cleanup(curl);
                return "vse ochen ploho :c";
            }

		}
    }


   // auto InstagramClient::search(){}// позже


    auto InstagramClient::callback(char *ptr_, size_t size_, size_t nmemb_, string &userdata_)->size_t
    {
        size_t real_size = size * nmemb;
        userdata_ += ptr;
        return real_size;

    }
}
