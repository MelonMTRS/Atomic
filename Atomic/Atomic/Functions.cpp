#include <random>
#include "./Functions.h"

int atomic::random(int min, int max) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distr(min, max);
	return distr(mt);
}