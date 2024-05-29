#ifndef CONTENTFINDER_H_
#define CONTENTFINDER_H_

#include "finderSettings.h"
#include <atomic>
#include <thread>
#include <list>
#include <condition_variable>

class ContentFinder
{
private:
  Finder::SearchParameters      search_params_;
  
  std::mutex                    search_mutex_;
  std::condition_variable       condition_var_;
  std::atomic_uint              active_thread_count_;

  //std::mutex                    thread_list_mutex_;
  //std::list<std::thread>        thread_list_;

public:
  // Not copyable or movable
  ContentFinder(const ContentFinder&) = delete;
  ContentFinder& operator=(const ContentFinder&) = delete;

  ContentFinder(const Finder::SearchParameters& settings);
  ~ContentFinder();

  void SearchFileContent(const std::filesystem::path& file);

  // Wait all content search threads to finish
  void WaitToComplete();

private:
  void ContentSerchThread(const std::filesystem::path& file);
};


#endif  // CONTENTFINDER_H_