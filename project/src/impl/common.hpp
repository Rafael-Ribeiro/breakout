#include "../common.hpp"

#include <chrono>
#include <random>

int random_int(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
   	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(gen);
}