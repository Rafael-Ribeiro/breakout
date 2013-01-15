#include "../common.hpp"

#include <chrono>
#include <random>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <cstring>

int random_int(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
   	
   	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(gen);
}

std::vector<std::string> list_dir(std::string path)
{
	std::vector<std::string> levels_list;

	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.c_str());

	if (dir == NULL)
		return levels_list;

	while ((ent = readdir(dir)) != NULL)
	{
		if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))
		{
			std::stringstream filepath;
			filepath << path << "/" << ent->d_name;
			levels_list.push_back(filepath.str());
		}
	}

	closedir(dir);

	return levels_list;
}