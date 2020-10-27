#ifndef ATOMIC_FUNCTIONS_H
#define ATOMIC_FUNCTIONS_H
#include <vector>
#include "./Item.h"

// Useful functions

namespace atomic {
	int random(const int& min, const int& max);
	template <typename Type>
	Type random_choice(const std::vector<Type>& arr) { return arr[atomic::random(0, arr.size() - 1)]; }
	std::string getDemandString(const atomic::Demand& demand);
	std::vector<std::string> split(const std::string& str, const char& separator);
	bool isStatusSuccess(const int& status_code);
	std::string lower(const std::string& str);
	std::string upper(const std::string& str);
}

#endif