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
    //client.check_connection();
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

  const unsigned int nthreads = atoi(argv[1]);
  const unsigned int max_nthreads = std::thread::hardware_concurrency();
  if(nthreads > max_nthreads)
  {
    cout << "threads must be <= " << max_nthreads << std::endl;
    return -1;
  }

  bool verbose = (atoi(argv[2]) != 0);

  std::vector<std::thread> threads;

  for(unsigned int i = 0; i < nthreads; ++i)
  {
    threads.push_back(std::thread(thread_func, i, verbose));
  }

  for(auto& thread: threads)
  {
    thread.join();
  }

  return 0;
}

