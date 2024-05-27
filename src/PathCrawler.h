#ifndef PATHCRAWLER_H_
#define PATHCRAWLER_H_

#include <filesystem>
#include <regex>

#include "finderSettings.h"

class PathCrawler
{
private:
  Finder::SearchParameters                      search_params_;
  bool                                          single_file_;
  bool                                          complete_;

  std::filesystem::recursive_directory_iterator recursive_directory_iterator_;
  std::filesystem::directory_iterator           directory_iterator_;
  std::regex                                    path_search_pattern_;

public:
  // Not copyable or movable
  PathCrawler(const PathCrawler&) = delete;
  PathCrawler& operator=(const PathCrawler&) = delete;

  // Setup PathCrawler
  PathCrawler(const Finder::SearchParameters& settings);

  // Get next matching file from the search directory
  std::optional<std::filesystem::path> GetNextFile();

private:
  // Genering replace method for strings
  void StringReplace(std::string& input, const std::string& fromWhat, const std::string& toWhat) const;

  // Convert path string to regexp search patter string
  std::string ConvertPathStringToRegexp(const std::string& path) const;

  // Check if file path matches the search criteries
  bool MathcFile(const std::filesystem::path& path) const;
};

#endif  // PATHCRAWLER_H_