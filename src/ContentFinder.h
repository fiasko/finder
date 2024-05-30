#ifndef CONTENTFINDER_H_
#define CONTENTFINDER_H_

#include "finderSettings.h"

#include <atomic>
#include <condition_variable>
#include <list>
#include <thread>

class ContentFinder
{
protected:
  Finder::SearchParameters          search_params_;
  
  mutable std::mutex                search_mutex_;
  mutable std::condition_variable   condition_var_;
  std::atomic_uint                  active_thread_count_;

public:
  // Not copyable or movable
  ContentFinder(const ContentFinder&) = delete;
  ContentFinder& operator=(const ContentFinder&) = delete;

  ContentFinder(const Finder::SearchParameters& settings);
  ~ContentFinder();

  void SearchFileContent(const std::filesystem::path& file);

  // Wait all content search threads to finish
  void WaitToComplete() const;

protected:
  void ContentSerchThread(const std::filesystem::path& file);
  virtual void PrintOutput(const std::filesystem::path& file, const std::string_view& content) const;
};

#endif  // CONTENTFINDER_H_