#ifndef __ATOMIC__FUNCTIONS__H
#define __ATOMIC__FUNCTIONS__H
#include <vector>
#include "./Item.h"

// Useful functions

namespace atomic {
	int random(const int& min, const int& max);
	template <typename Type>
	Type random_choice(std::vector<Type> arr) { return arr[atomic::random(0, arr.size() - 1)]; }
	std::string getItemStringDemand(const atomic::Demand& demand);
	std::vector<std::string> split(const std::string& str, const char& separator);
}

#endif