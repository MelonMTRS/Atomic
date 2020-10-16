#ifndef __ATOMIC__ITEM__H
#define __ATOMIC__ITEM__H
#include <string>

namespace atomic {
	struct RolimonsItem {
		const std::string name;
		const std::int64_t id;
		const std::int64_t rap;
		const std::int64_t value;
	};

	struct Item {
		const std::string name;
		const std::int64_t id;
		const std::int64_t userAssetId; // Unique Identifier Id
		const std::int64_t rap;
		std::int64_t value = -1;
	};
}

#endif