#include <iostream>
#include <thread>

#include <filesystem>

#include "finderSettings.h"
#include "Crawler.h"

using namespace std::literals;

int main(int argc, char* argv[]) {
  
    SearchParameters searchParam = { false, false, "", "" };

    for (int i = 1; i < argc; i++)
    {
        if ("-r"s == argv[i])
        {
            searchParam.bRecursive = true;
        }
        else if ("-r"s == argv[i])
        {
            searchParam.bRegExpPatter = true;
        }
        else if (searchParam.searchPattern.empty())
        {
            searchParam.searchPattern = argv[i];
        }
        else if (searchParam.searchPath.empty())
        {
            searchParam.searchPath = argv[i];
        }
        else
        {
            PrintHelp();
            return 1;
        }
    }

    if (searchParam.searchPath.empty())
    {
        searchParam.searchPath = ".";
    }


    // get CPU core count
    const auto cpuCoreCount = std::thread::hardware_concurrency();

    std::cout << "Hello, World! with "<< cpuCoreCount <<" CPU cores! argc="<< argc << std::endl;
    //  X "..\\..\\..\\test\\testdata\\*.*"
    Crawler c(searchParam.searchPath);
    return 0;
}