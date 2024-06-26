#include <filesystem>
#include <format>
#include <iostream>
#include <optional>
#include <thread>

#include "finderSettings.h"
#include "PathCrawler.h"
#include "ContentFinder.h"


int main(int argc, const char* argv[])
{
  // parse finder settings from arguments 
  auto searchParam = Finder::ParseArguments(argc, argv);

  // Print help and break if needed
  if (!searchParam.has_value()) {
    Finder::PrintHelp();
    return 1;
  }

  PathCrawler crawler(searchParam.value());
  ContentFinder finder(searchParam.value());

  std::optional<std::filesystem::path> file;
  while ((file = crawler.GetNextFile()).has_value()) {
    finder.SearchFileContent(file.value());
  }

  std::cout << "WaitToComplete\n";
  finder.WaitToComplete();
  return 0;
}