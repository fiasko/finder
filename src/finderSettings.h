#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <optional>

namespace Finder
{
    struct SearchParameters
    {
        bool bRecursive;
        bool bRegExpPatter;
        std::string searchPattern;
        std::filesystem::path searchPath;
    };

    static void PrintHelp()
    {
        std::cout <<
            "Usage: finder [OPTION]... PATTERN [FILE]\n"
            "  -G             PATTERN is basic regular expressions\n"
            "  -r             recursive search\n";
    }

    static std::optional<SearchParameters> ParseArguments(const int argc, const char* argv[])
    {
        using namespace std::literals;

        SearchParameters searchParam = { false, false, "", "" };

        for (int i = 1; i < argc; i++)
        {
            if ("-r"s == argv[i])
            {
                searchParam.bRecursive = true;
            }
            else if ("-G"s == argv[i])
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
                return {};
            }
        }

        if (searchParam.searchPath.empty())
        {
            searchParam.searchPath = ".";
        }

        return searchParam;
    }
}