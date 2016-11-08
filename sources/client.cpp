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
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.instagram.com/v1/users/self/?access_token=4079059384.39f3c6e.29a442eca7f54865a92e071db07cd987"); 
        res = curl_easy_perform(curl);
        if (res == CURLE_OK)
          {
            cout << "authentication is successful" << endl;
            return true;
          }
        
          curl_easy_cleanup(curl);
      }
    
   }
   
  
  
  auto InstagramClient::get_followers ()-> bool
  { 
    CURL *curl = curl_easy_init();
      if (curl)
      {
        
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.instagram.com/v1/users/self/follows?access_token=4079059384.39f3c6e.29a442eca7f54865a92e071db07cd987"); 
        res = curl_easy_perform(curl);
        if (res == CURLE_OK)
        {}
      }
  
  }
}
