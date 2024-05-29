#include "ContentFinder.h"

#include <iostream>
#include <fstream>
#include <array>
#include <string_view>
#include <format>
#include <regex>
#include <chrono>

ContentFinder::ContentFinder(const Finder::SearchParameters& settings)
  : search_params_(settings),
  active_thread_count_(0)
{
}

ContentFinder::~ContentFinder() {
  if (active_thread_count_ > 0) {
    WaitToComplete();
  }
}

void ContentFinder::SearchFileContent(const std::filesystem::path& file) {
  using namespace std::chrono_literals;

  // wait thread slot to become available
  std::unique_lock lk(search_mutex_);
  while (!condition_var_.wait_for(lk, 10ms, [this] { return active_thread_count_ < std::thread::hardware_concurrency(); })) {}
  active_thread_count_++;

  std::thread t(&ContentFinder::ContentSerchThread, this, file);
  t.detach();
}

void ContentFinder::WaitToComplete() {
  using namespace std::chrono_literals;

  std::unique_lock lk(search_mutex_);
  if (!condition_var_.wait_for(lk, 1min, [this] { return active_thread_count_ == 0; })) {
    std::cerr << "WaitToComplete timeout!\n";
  }
}

void ContentFinder::ContentSerchThread(const std::filesystem::path& file) {
  std::ifstream f(file);
  std::array<char, 512> line;

  std::regex re(search_params_.use_reg_exp ? search_params_.search_pattern : "");

  while (f.getline(&line[0], line.size())) {
    std::string_view line_str(&line[0]);

    // search output not bufferd and thread output is not synchronized
    if (search_params_.use_reg_exp) {
      // regexp pattern search
      if (std::regex_match(line_str.data(), re)) {
        std::cout << std::format("{}:{}\n", file.string(), line_str);
      }
    }
    else {
      // basic string search
      if (line_str.find(search_params_.search_pattern) != std::string_view::npos) {
        std::cout << std::format("{}:{}\n", file.string(), line_str);
      }
    }
  }

  // signal about thread slot being available
  active_thread_count_--;
  condition_var_.notify_one();
}
