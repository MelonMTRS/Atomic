#ifndef ATOMIC_FUNCTIONS_H
#define ATOMIC_FUNCTIONS_H
#include <vector>
#include "./Item.h"

// Useful functions

namespace atomic {
	int random(const int& min, const int& max);
	std::string getDemandString(const atomic::Demand& demand);
	int getDemandId(const atomic::Demand& demand);
	std::vector<std::string> split(const std::string& str, const char& separator);
	bool isStatusSuccess(const int& status_code);
	std::string lower(const std::string& str);
	std::string upper(const std::string& str);
	void clear();

	template<typename Type>
	Type random_choice(const std::vector<Type>& v) {
		return v[atomic::random(0, v.size() - 1)];
	}
}

#endif