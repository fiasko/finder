#include <iostream>
#include <thread>
#include <optional>
#include <filesystem>

#include "finderSettings.h"
#include "PathCrawler.h"


int main(int argc, const char* argv[])
{
    // parse finder settings from arguments 
    auto searchParam = Finder::ParseArguments(argc, argv);

    // Print help and break if needed
    if (!searchParam.has_value())
    {
        Finder::PrintHelp();
        return 1;
    }


    // get CPU core count
    const auto cpuCoreCount = std::thread::hardware_concurrency();

    std::cout << "Hello, World! with "<< cpuCoreCount <<" CPU cores! argc="<< argc << std::endl;
    //  X "..\\..\\..\\test\\testdata\\*.*"
    PathCrawler crawler(searchParam.value());
    return 0;
}