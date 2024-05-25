#pragma once
#include <filesystem>

#include "finderSettings.h"

class PathCrawler
{

public:
	PathCrawler(const Finder::SearchParameters& settings);

private:
	void stringReplace(std::string& input, const std::string& fromWhat, const std::string& toWhat);
	std::string ConvertWildcardsToRegexp(const std::string& wcs);
	std::vector<std::string> GetFileList(const std::filesystem::path& directory, const std::string& filenamePattern);
};