#ifndef __ATOMIC__FUNCTIONS__H
#define __ATOMIC__FUNCTIONS__H
#include <vector>
#include "./Item.h"

// Useful functions

namespace atomic {
	int random(int min, int max);
	std::string getItemStringDemand(atomic::Demand demand);
	std::vector<std::string> split(std::string str, char separator);
}

#endif