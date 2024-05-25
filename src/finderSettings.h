#pragma once
#include <string>
#include <filesystem>

struct SearchParameters
{
    bool bRecursive;
    bool bRegExpPatter;
    std::string searchPattern;
    std::filesystem::path searchPath;
};


void PrintHelp()
{
    std::cout <<
        "Usage: finder [OPTION]... PATTERN [FILE]\n"
        "  -G             PATTERN is basic regular expressions\n"
        "  -r             recursive search\n";
}