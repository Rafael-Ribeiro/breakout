#pragma once

#include <vector>
#include <string>

#define MARKUSED(X)  ((void)(&(X)))

std::vector<std::string> list_dir(std::string path);
int random_int(int min, int max);