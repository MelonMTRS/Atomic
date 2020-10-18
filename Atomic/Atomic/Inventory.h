#ifndef __ATOMIC__INVENTORY__H
#define __ATOMIC__INVENTORY__H
#include <vector>
#include <functional>
#include "./Item.h"

namespace atomic {
	using ItemContainer = std::vector<atomic::Item>;
	class Inventory {
	private:
		ItemContainer m_inventory;
		bool itemContainsValues = true;
	public:
		Inventory() = default;
		Inventory(ItemContainer inventory)
			: m_inventory{inventory}
		{
			for (auto item = inventory.begin(); item != inventory.end(); ++item) {
				if (item->value == -1)
					this->itemContainsValues = false;
			}
		}

		inline void addItem(const atomic::Item& item) { this->m_inventory.push_back(item); }
		[[nodiscard]] atomic::Item& getRandomItem();
		[[nodiscard]] inline const ItemContainer& getInventory() const noexcept { return this->m_inventory; }
		[[nodiscard]] size_t item_count() const noexcept { return this->m_inventory.size(); }
		[[nodiscard]] bool itemHasValues() { return this->itemContainsValues; }

		[[nodiscard]] ItemContainer::iterator begin() noexcept { return this->m_inventory.begin(); }
		[[nodiscard]] ItemContainer::iterator end() noexcept { return this->m_inventory.end(); }

		// Searching / Indexing
		[[nodiscard]] atomic::Item& operator[](int index) { return this->m_inventory[index]; }
		[[nodiscard]] atomic::Item& findItemByName(const std::string& name);
		[[nodiscard]] atomic::Item& findItemById(int assetId);
		[[nodiscard]] ItemContainer itemMatch(const std::function<bool(const atomic::Item&)>& function);
	};
}

#endif