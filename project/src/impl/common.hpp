#include "../common.hpp"

#include <chrono>
#include <random>

int random_int(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
   	
   	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(gen);
}