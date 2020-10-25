#ifndef __ATOMIC__FUNCTIONS__H
#define __ATOMIC__FUNCTIONS__H
#include <vector>
#include "./Item.h"

// Useful functions

namespace atomic {
	int random(const int& min, const int& max);
	std::string getItemStringDemand(atomic::Demand demand);
	std::vector<std::string> split(const std::string& str, const char& separator);
}

#endif