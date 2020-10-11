#include <string>
#ifndef __ATOMIC__ITEM__H
#define __ATOMIC__ITEM__H

namespace atomic {
	struct Item {
		const std::string name;
		const std::int64_t id;
		const std::int64_t userAssetId; // Unique Identifier Id
		const int rap;
	};
}

#endif