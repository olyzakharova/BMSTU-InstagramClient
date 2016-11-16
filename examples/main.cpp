#include "instagram/client.hpp"

int main()
{
  Instagram::InstagramClient client;
  client.check_connection();
  client.get_most_recent_media();
  //client.liked_by_user();


  return 0;
}
