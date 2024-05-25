#include "Crawler.h"
#include <iostream>

namespace fs = std::filesystem;

Crawler::Crawler(const std::filesystem::path& root)
{
	std::cout << fs::absolute(root).string();
	

	if (fs::exists(root))
	{
		std::cout << root.filename().string();

		if (fs::is_regular_file(root))
		{
			std::cout << std::endl << root.filename().string() << " is a regular file\n";
		}
		else if (fs::is_directory(root))
		{
			std::cout << " is a directory\n";
		}
	}
	else if (fs::exists(root.parent_path()))
	{
		std::cout << "path exists but file ["<< root.filename().string() << "] does not\n";
	}
	else
	{
		std::cout << " does not exist\n";
	}
}
