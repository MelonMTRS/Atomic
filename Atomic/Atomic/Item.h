#ifndef ATOMIC_ITEM_H
#define ATOMIC_ITEM_H
#include <string>

namespace atomic {
	enum class Demand {
		NotAssigned,
		Terrible,
		Low,
		Normal,
		High,
		Amazing,
		Unknown
	};

	class Item {
	public:
		std::string name;
		std::int64_t id;
		std::int64_t rap;
		std::int64_t value = -1;
		atomic::Demand demand = atomic::Demand::NotAssigned;

		void operator=(const Item* newItem) { *this = newItem; }

		template<typename Item_> bool operator>(const Item_ item) { return this->value > item.value; }
		template<typename Item_> bool operator<(const Item_ item) { return this->value < item.value; }
		template<typename Item_> bool operator>=(const Item_ item) { return this->value >= item.value; }
		template<typename Item_> bool operator<=(const Item_ item) { return this->value <= item.value; }
		template<typename Item_> bool operator==(const Item_ item) { return this->value == item.value; }
		template<typename Item_> bool operator!=(const Item_ item) { return this->value != item.value; }
#ifdef __cpp_lib_three_way_comparison
		template<typename Item_> bool operator<=>(const _Item item) { return this->value <=> item.value; }
#endif
	};

	class UniqueItem : public Item {
	public:
		std::int64_t userAssetId;

		UniqueItem() = default;
		UniqueItem(std::string p_name, std::int64_t p_id, std::int64_t p_userAssetId,
		           std::int64_t p_rap, std::int64_t p_value=-1, atomic::Demand p_demand=Demand::NotAssigned)
			: Item{ p_name, p_id, p_rap, p_value, p_demand }, userAssetId{p_userAssetId} {}

		Item getItem() {
			return Item{ name, id, rap, value, demand };
		}

		void operator=(const UniqueItem* newItem) { *this = newItem; }
	};
}

#endif