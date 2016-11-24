#include "instagram/client.hpp"
#include <stdexcept>
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <vector>
#include <mutex>
#include <chrono>

using namespace std;

mutex m;

std::string get_now_time()
{
  auto p = chrono::system_clock::now();
  auto t = chrono::system_clock::to_time_t(p);
  return std::ctime(&t);
}

void thread_func(unsigned int id, bool v)
{
  lock_guard<mutex> lock(m);
  if(v)
  {
    cout << "thread id: " << id << endl;
    cout << "start time: " << get_now_time();
  }
  try
  {
    Instagram::InstagramClient client;
    cout << "link: " << client.get_most_recent_media() << endl;
  }
  catch(exception& e)
  {
    cout << "exception: " << e.what() << endl;
  }
  if(v)
  {
    cout << "end time: " << get_now_time() << endl;
  }
}

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    cout << "usage: " << argv[0] << " {threads} {verbose}" << std::endl;
    return -1;
  }

  const unsigned long nthreads = strtol(argv[1], NULL, 10);
  const unsigned int max_nthreads = std::thread::hardware_concurrency();
  if(nthreads == 0)
  {
    cout << "threads must be integer > 0" << std::endl;
    return -1;
  }
  else if(nthreads > max_nthreads)
  {
    cout << "threads must be <= " << max_nthreads << std::endl;
    return -1;
  }

  bool verbose = (strtol(argv[2], NULL, 10) != 0);

  std::vector<std::thread> threads;

  for(unsigned int i = 0; i < nthreads; ++i)
  {
    threads.push_back(std::thread(thread_func, i, verbose));
  }

  for(auto& thread: threads)
  {
    if(thread.joinable())
      thread.join();
  }

  return 0;
}

