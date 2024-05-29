#include "PathCrawler.h"
#include <iostream>
#include <regex>

namespace fs = std::filesystem;

PathCrawler::PathCrawler(const Finder::SearchParameters& settings)
  : search_params_(settings),
  single_file_(false),
  complete_(false)
{
  if (fs::exists(search_params_.search_path) && fs::is_regular_file(search_params_.search_path)) {
    // user defined single file. No directory search required
    single_file_ = true;
  }
  else if (fs::exists(search_params_.search_path) && (fs::is_directory(search_params_.search_path))) {
    // user defined search directory. Initialize required directory iterator and file search pattern
    path_search_pattern_ = ".*";

    if (search_params_.recursive_search) {
      recursive_directory_iterator_ = fs::recursive_directory_iterator{ search_params_.search_path };
    }
    else {
      directory_iterator_ = fs::directory_iterator{ search_params_.search_path };
    }
  }
  else if (search_params_.search_path.string().find_first_of("[*") != std::string::npos) {
    // user included wildcards to the file search path.
    // Initialize required directory iterator and path search pattern
    path_search_pattern_ = ConvertPathStringToRegexp(search_params_.search_path.string());

    if (search_params_.recursive_search) {
      recursive_directory_iterator_ = fs::recursive_directory_iterator{ search_params_.search_path.parent_path() };
    }
    else {
      directory_iterator_ = fs::directory_iterator{ search_params_.search_path.parent_path() };
    }
  }
  else
  {
    complete_ = true;
    std::cerr << "File does not exist\n";
  }
}

std::optional<std::filesystem::path> PathCrawler::GetNextFile()
{
  if (complete_) {
    return {};
  }
  else if (single_file_) {
    complete_ = true;
    return search_params_.search_path;
  }
  else {
    // find next matching file from the directory
    if (search_params_.recursive_search) {
      while (recursive_directory_iterator_ != std::filesystem::end(recursive_directory_iterator_)) {
        if (MathcFile(recursive_directory_iterator_->path().string())) {
          auto p = recursive_directory_iterator_->path();
          ++recursive_directory_iterator_;
          return p;
        }
        ++recursive_directory_iterator_;
      }
    }
    else {
      while (directory_iterator_ != std::filesystem::end(directory_iterator_)) {
        if (MathcFile(directory_iterator_->path().string())) {
          auto p = directory_iterator_->path();
          ++directory_iterator_;
          return p;
        }
        ++directory_iterator_;
      }
    }

    complete_ = true;
    return {};
  }
}

void PathCrawler::StringReplace(std::string& input, const std::string& from_what, const std::string& to_what) const {
  size_t pos = 0;
  while ((pos = input.find(from_what, pos)) != std::string::npos) {
    input.replace(pos, from_what.length(), to_what);
    pos += to_what.length();
  }
}

std::string PathCrawler::ConvertPathStringToRegexp(const std::string& path) const {
  std::string searchPattern = path;
  StringReplace(searchPattern, R"(\)", R"(\\)");      // escape Windows path symbols
  StringReplace(searchPattern, R"(.)", R"(\.)");      // escape dot symbols
  StringReplace(searchPattern, R"(*)", R"([^\\/]*)");  // convert wildcard symbols
  return  "^" + searchPattern + "$";                  // add word boundaries
}

bool PathCrawler::MathcFile(const std::filesystem::path& path) const {
  return fs::is_regular_file(path) && std::regex_match(path.string(), path_search_pattern_);
}
