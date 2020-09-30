#include <string>
#ifndef __ATOMIC__ITEM__H
#define __ATOMIC__ITEM__H

namespace atomic {
	struct Item {
		/*
			Represents a roblox item
		*/
		const std::string name;
		const int id;
		const int rap;
	};
}

#endif