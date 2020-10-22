#ifndef __ATOMIC__ITEM__H
#define __ATOMIC__ITEM__H
#include <string>

namespace atomic {
	/*
	some kids may ask why there is both NotSet and NotAssigned
	and to those kids i say ur a dumb idiot cum poop
	*/
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

	struct Item {
		const std::string name;
		const std::int64_t id;
		const std::int64_t rap;
		std::int64_t value = -1;
		atomic::Demand demand = atomic::Demand::NotSet;
	};

	struct UniqueItem {
		const std::string name;
		const std::int64_t id;
		const std::int64_t userAssetId; // Unique Identifier Id
		const std::int64_t rap;
		std::int64_t value = -1;
		atomic::Demand demand = atomic::Demand::NotSet;

		Item getRegularItem() {
			return Item{ name, id, rap, value, demand };
		}
	};
}

#endif