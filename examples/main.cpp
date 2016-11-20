#include "instagram/client.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

int main()
{
  try
  {
    Instagram::InstagramClient client;
    client.check_connection();
    client.get_most_recent_media();
  
  }
  catch(exception& e)
  {
    cout << "exception: " << e.what() << std::endl;
  }


  return 0;
}

