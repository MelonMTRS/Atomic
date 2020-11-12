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

		void operator=(const Item* newItem) {
			*this = newItem;
		}
	};

	class UniqueItem : public Item {
	public:
		std::int64_t userAssetId;
		UniqueItem() = default;
		UniqueItem(std::string p_name, std::int64_t p_id, std::int64_t p_userAssetId,
		   std::int64_t p_rap, std::int64_t p_value=-1, atomic::Demand p_demand = Demand::NotSet)
			: Item{ p_name, p_id, p_rap, p_value, p_demand }, userAssetId{p_userAssetId} {}

		Item getRegularItem() {
			return Item{ name, id, rap, value, demand };
		}

		void operator=(const UniqueItem* newItem) {
			*this = newItem;
		}
	};
}

#endif