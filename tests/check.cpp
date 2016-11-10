#include "catch.hpp"
#include "include/client.hpp"

SCENARIO ("if access token is correct")
{   
    GIVEN("access token")
    { 
      string token= "4079059384.39f3c6e.29a442eca7f54865a92e071db07cd987";
      InstagramCLient koko;
      WHEN("token is correct")
      {
        THEN("C:")
        {
           REQUIRE(koko.check_connection == true;);
        }
        
      }
    
    }
}

SCENARIO ("if access token isn't correct")
{   
    GIVEN("access token")
    { 
      string token="0000000000";
      InstagramCLient koko;
      WHEN("token is correct")
      {
        THEN(":C")
        {
           REQUIRE(koko.check_connection == false);
        }
      }
         
    }
}

