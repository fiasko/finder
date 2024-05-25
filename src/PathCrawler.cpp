#include "PathCrawler.h"
#include <iostream>
#include <regex>

namespace fs = std::filesystem;

PathCrawler::PathCrawler(const Finder::SearchParameters& settings)
{
	if (fs::exists(settings.searchPath))
	{
		std::cout << "[" << fs::absolute(settings.searchPath).string() << "] ";
		std::cout << settings.searchPath.filename().string();

		if (fs::is_regular_file(settings.searchPath))
		{
			std::cout << std::endl << settings.searchPath.filename().string() << " is a regular file\n";
		}
		else if (fs::is_directory(settings.searchPath))
		{
			std::cout << " is a directory\n";
		}
	}
	else if (fs::exists(settings.searchPath.parent_path()))
	{
		std::cout << "[" << fs::absolute(settings.searchPath).parent_path().string() << "] path exists but ";
		if (settings.searchPath.filename().string().find("*") != std::string::npos)
		{
			std::cout << "filename has wildcards [" << settings.searchPath.filename().string() << "]\n";

			auto filelist = GetFileList(fs::absolute(settings.searchPath), settings.searchPath.filename().string(), settings.bRecursive);

			for (const auto& p : filelist)
			{
				std::cout << "Path match: " << p.string() << std::endl;
			}
		}
		else
		{
			std::cout << "file [" << settings.searchPath.filename().string() << "] does not\n";
		}
		
	}
	else
	{
		std::cout << " does not exist\n";
	}
}

void PathCrawler::stringReplace(std::string& input, const std::string& fromWhat, const std::string& toWhat)
{
	size_t pos = 0;
	while ((pos = input.find(fromWhat, pos)) != std::string::npos)
	{
		input.replace(pos, fromWhat.length(), toWhat);
		pos += toWhat.length();
	}
}

std::string PathCrawler::ConvertWildcardsToRegexp(const std::string& wcs)
{
	std::string searchPattern = wcs;
	stringReplace(searchPattern, ".", "\\.");
	stringReplace(searchPattern, "*", ".*");

	return  "^" + searchPattern + "$";
}

std::vector<std::filesystem::path> PathCrawler::GetFileList(const std::filesystem::path& directory, const std::string& filenamePattern, const bool bRecursive)
{
	std::vector<fs::path> fileList;

	std::string searchPatter = ConvertWildcardsToRegexp(filenamePattern);
	
	std::cout << "file name searchPattern: " << searchPatter << std::endl;

	std::regex regex(searchPatter);

	auto MathcFile = [&regex](const fs::path& dir) -> bool { return (fs::is_regular_file(dir) && std::regex_match(dir.filename().string(), regex)); };

	if (bRecursive)
	{
		for (auto const& directory : fs::recursive_directory_iterator{ directory.parent_path() })
		{
			if (MathcFile(directory.path()))
			{
				fileList.push_back(directory.path());
			}
		}
	}
	else
	{
		for (auto const& directory : fs::directory_iterator{ directory.parent_path() })
		{
			if (MathcFile(directory.path()))
			{
				fileList.push_back(directory.path());
			}
		}
	}

	return fileList;
}
