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

			GetFileList(fs::absolute(settings.searchPath), settings.searchPath.filename().string());
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

std::vector<std::string> PathCrawler::GetFileList(const std::filesystem::path& directory, const std::string& filenamePattern)
{
	std::vector<std::string> fileList;

	std::string searchPatter = ConvertWildcardsToRegexp(filenamePattern);
	
	std::cout << "searchPattern: " << searchPatter << std::endl;

	std::regex regex(searchPatter);

	for (auto const& directory : std::filesystem::directory_iterator{ directory.parent_path()})
	{
		if (std::filesystem::is_regular_file(directory)) {
			if (std::regex_match(directory.path().filename().string(), regex)) {
				std::cout << directory.path() << '\n';
			}
		}
	}

	return fileList;
}
