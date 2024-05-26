#include "PathCrawler.h"
#include <iostream>
#include <regex>

namespace fs = std::filesystem;

PathCrawler::PathCrawler(const Finder::SearchParameters& settings)
	: search_params_(settings),
	single_file_(false),
	complete_(false)
{
	if (fs::exists(search_params_.search_path) && fs::is_regular_file(search_params_.search_path))
	{
		single_file_ = true;
		//std::cout << std::endl << search_params_.search_path.filename().string() << " is a regular file\n";

		//std::cout << "[" << fs::absolute(search_params_.search_path).string() << "] ";
		//std::cout << search_params_.search_path.filename().string();
		
	}
	else if (fs::exists(search_params_.search_path) && (fs::is_directory(search_params_.search_path)))
	{
		//std::cout << " is a directory\n";

		path_search_pattern_ = ".*";

		if (search_params_.recursive)
		{
			recursive_directory_iterator_ = fs::recursive_directory_iterator{ search_params_.search_path };
		}
		else
		{
			directory_iterator_ = fs::directory_iterator{ search_params_.search_path };
		}
	}
	else if (fs::exists(search_params_.search_path.parent_path()))
	{
		//std::cout << "[" << fs::absolute(search_params_.search_path).parent_path().string() << "] path exists but ";
		if (search_params_.search_path.filename().string().find("*") != std::string::npos)
		{
			//std::cout << "filename has wildcards [" << search_params_.search_path.filename().string() << "]\n";

			path_search_pattern_ = ConvertPathStringToRegexp(search_params_.search_path.string());

			if (search_params_.recursive)
			{
				recursive_directory_iterator_ = fs::recursive_directory_iterator{ search_params_.search_path.parent_path() };
			}
			else
			{
				directory_iterator_ = fs::directory_iterator{ search_params_.search_path.parent_path() };
			}
		}
		else
		{
			//std::cout << "file [" << search_params_.search_path.filename().string() << "] does not\n";
			complete_ = true;
		}
	}
	else
	{
		std::cerr << "File does not exist\n";
	}
}

std::optional<std::filesystem::path> PathCrawler::GetNextFile()
{
	if (complete_)
	{
		return {};
	}
	else if (single_file_)
	{
		complete_ = true;
		return search_params_.search_path;
	}
	else
	{
		if (search_params_.recursive)
		{
			while (recursive_directory_iterator_ != std::filesystem::end(recursive_directory_iterator_))
			{
				if (MathcFile(recursive_directory_iterator_->path().string()))
				{
					auto p = recursive_directory_iterator_->path();
					++recursive_directory_iterator_;
					return p;
				}
				++recursive_directory_iterator_;
			}
		}
		else
		{
			while (directory_iterator_ != std::filesystem::end(directory_iterator_))
			{
				if (MathcFile(directory_iterator_->path().string()))
				{
					auto p = directory_iterator_->path();
					++directory_iterator_;
					return p;
				}
				++directory_iterator_;
			}
		}

		complete_ = true;
		return {};
	}
}

void PathCrawler::StringReplace(std::string& input, const std::string& from_what, const std::string& to_what)
{
	size_t pos = 0;
	while ((pos = input.find(from_what, pos)) != std::string::npos)
	{
		input.replace(pos, from_what.length(), to_what);
		pos += to_what.length();
	}
}

std::string PathCrawler::ConvertPathStringToRegexp(const std::string& path)
{
	std::string searchPattern = path;
	StringReplace(searchPattern, "\\", "\\\\");	// escape Windows path symbols
	StringReplace(searchPattern, ".", "\\.");	// escape dot symbols
	StringReplace(searchPattern, "*", "[^\\\\]*");	// convert wildcard symbols

	return  "^" + searchPattern + "$";			// require explicit pattern match
}

bool PathCrawler::MathcFile(const std::filesystem::path& dir)
{
	return fs::is_regular_file(dir) && std::regex_match(dir.string(), path_search_pattern_);
}
