#ifndef __ATOMIC__ITEM__H
#define __ATOMIC__ITEM__H
#include <string>

namespace atomic {
	enum class Demand {
		NotSet,
		NotAssigned,
		Terrible,
		Low,
		Normal,
		High,
		Amazing,
		Unknown
	};

	struct RolimonsItem {
		const std::string name;
		const std::int64_t id;
		const std::int64_t rap;
		const std::int64_t value;
		const atomic::Demand demand;
	};

	struct Item {
		const std::string name;
		const std::int64_t id;
		const std::int64_t userAssetId; // Unique Identifier Id
		const std::int64_t rap;
		std::int64_t value = -1;
		atomic::Demand demand = atomic::Demand::NotSet;
	};
}

#endif