#include "instagram/client.hpp"

int main()
{
  Instagram::InstagramClient client;
  client.check_connection();

  return 0;
}
