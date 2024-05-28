#include "ContentFinder.h"

#include <iostream>
#include <fstream>
#include <array>
#include <string_view>
#include <format>
#include <regex>
#include <chrono>

ContentFinder::ContentFinder(const Finder::SearchParameters& settings)
  : search_params_(settings)
{
}

ContentFinder::~ContentFinder() {
  if (!thread_list_.empty()) {
    WaitToComplete();
  }
}

void ContentFinder::SearchFileContent(const std::filesystem::path& file) {
  using namespace std::chrono_literals;

  std::lock_guard<std::mutex> lg(thread_list_mutex_);
  while (thread_list_.size() >= std::thread::hardware_concurrency()) {
    thread_list_.remove_if([](const std::thread& t) { return t.joinable(); });
    if (thread_list_.size() < std::thread::hardware_concurrency()) {
      break;
    }

    // this is ugly, but this architecture has its limitations...
    std::this_thread::sleep_for(1ms);
  }

  thread_list_.emplace_back(&ContentFinder::ContentSerchThread, this, file);
}

void ContentFinder::WaitToComplete() {
  try {
    for (auto& t : thread_list_) {
      t.join();
    }
    thread_list_.clear();
  }
  catch (const std::system_error& e) {
    std::cerr << std::format("Thread error: {}", e.what());
  }
  catch (const std::exception& e) {
    std::cerr << std::format("WaitToComplete Eerror: {}", e.what());
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
}
