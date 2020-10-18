#include <random>
#include "./Functions.h"

int atomic::random(int min, int max) {
	std::random_device device;
	std::mt19937 mt(device());
	std::uniform_int_distribution<int> db(min, max);
	return db(mt);
}