#ifndef PATHCRAWLER_H_
#define PATHCRAWLER_H_

#include <filesystem>
#include <regex>

#include "finderSettings.h"

class PathCrawler
{
private:
	Finder::SearchParameters						search_params_;
	bool											single_file_;
	bool											complete_;

	std::filesystem::recursive_directory_iterator	recursive_directory_iterator_;
	std::filesystem::directory_iterator				directory_iterator_;
	std::regex										path_search_pattern_;
	

public:
	PathCrawler(const Finder::SearchParameters& settings);

	std::optional<std::filesystem::path> GetNextFile();

private:
	void		StringReplace(std::string& input, const std::string& fromWhat, const std::string& toWhat);
	std::string ConvertPathStringToRegexp(const std::string& path);
	bool		MathcFile(const std::filesystem::path& dir);
	//std::vector<std::filesystem::path> GetFileList(const std::filesystem::path& directory, const std::string& filenamePattern, const bool bRecursive);
};

#endif  // PATHCRAWLER_H_