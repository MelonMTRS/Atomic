#include <string>
#ifndef __ATOMIC__ITEM__H
#define __ATOMIC__ITEM__H

namespace atomic {
	struct Item {
		const std::string name;
		const int id;
		const int userAssetId; // Unique Identifier Id
		const int rap;
	};
}

#endif