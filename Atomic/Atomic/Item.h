#ifndef ATOMIC_ITEM_H
#define ATOMIC_ITEM_H
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
		std::string name;
		std::int64_t id;
		std::int64_t rap;
		std::int64_t value = -1;
		atomic::Demand demand = atomic::Demand::NotSet;

		void operator=(const Item& newItem) {
			this->name = newItem.name;
			this->id = newItem.id;
			this->rap = newItem.rap;
			this->value = newItem.value;
			this->demand = newItem.demand;
		}
	};

	struct UniqueItem {
		std::string name;
		std::int64_t id;
		std::int64_t userAssetId; // Unique Identifier Id
		std::int64_t rap;
		std::int64_t value = -1;
		atomic::Demand demand = atomic::Demand::NotSet;

		Item getRegularItem() {
			return Item{ name, id, rap, value, demand };
		}

		void operator=(const UniqueItem& newItem) {
			this->name = newItem.name;
			this->id = newItem.id;
			this->userAssetId = newItem.userAssetId;
			this->rap = newItem.rap;
			this->value = newItem.value;
			this->demand = newItem.demand;
		}
	};
}

#endif