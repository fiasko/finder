#ifndef FINDERSETTINGS_H_
#define FINDERSETTINGS_H_

#include <iostream>
#include <string>
#include <filesystem>
#include <optional>

namespace Finder
{
  struct SearchParameters {
    bool recursive_search;
    bool use_reg_exp;
    std::string search_pattern;
    std::filesystem::path search_path;
  };

  static void PrintHelp()
  {
    std::cout <<
      "Usage: finder [OPTION]... PATTERN [FILE]\n"
      "  -G             PATTERN is basic regular expressions\n"
      "  -r             recursive search\n";
  }

  static std::optional<SearchParameters> ParseArguments(const int argc, const char* argv[]) {
    using namespace std::literals;

    SearchParameters searchParam = { false, false, "", "" };

    for (int i = 1; i < argc; i++) {
      if ("-r"s == argv[i]) {
        searchParam.recursive_search = true;
      }
      else if ("-G"s == argv[i]) {
        searchParam.use_reg_exp = true;
      }
      else if (searchParam.search_pattern.empty()) {
        searchParam.search_pattern = argv[i];
      }
      else if (searchParam.search_path.empty()) {
        searchParam.search_path = argv[i];
      }
      else {
        return {};
      }
    }
    
    if (searchParam.search_pattern.empty())
    {
      return {};
    }
    
    if (searchParam.search_path.empty()) {
      searchParam.search_path = ".";
    }

    return searchParam;
  }
} // namespace Finder

#endif  // FINDERSETTINGS_H_
