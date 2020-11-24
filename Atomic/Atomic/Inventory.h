#ifndef ATOMIC_INVENTORY_H
#define ATOMIC_INVENTORY_H
#include <functional>
#include <vector>
#include "./Item.h"

namespace atomic {
	using ItemContainer = std::vector<atomic::UniqueItem>;
	class Inventory {
	private:
		ItemContainer m_inventory;
	public:
		Inventory() = default;
		Inventory(const ItemContainer& inventory)
			: m_inventory{inventory}
		{
		}

		inline void addItem(const atomic::UniqueItem& item) { this->m_inventory.push_back(item); }
		[[nodiscard]] const atomic::UniqueItem getRandomItem() const;
		[[nodiscard]] const atomic::UniqueItem getRandomItem(const std::vector<std::string>& notForTrade) const;
		[[nodiscard]] inline const ItemContainer& getInventory() const noexcept { return this->m_inventory; }
		[[nodiscard]] inline const size_t item_count() const noexcept { return this->m_inventory.size(); }
		[[nodiscard]] const ItemContainer::iterator begin() noexcept { return this->m_inventory.begin(); }
		[[nodiscard]] const ItemContainer::iterator end() noexcept { return this->m_inventory.end(); }
		[[nodiscard]] ItemContainer items() const noexcept { return this->m_inventory; }
		// Searching / Indexing
		[[nodiscard]] atomic::UniqueItem operator[](int index) const { return this->m_inventory[index]; }
		[[nodiscard]] atomic::UniqueItem& findItemByName(const std::string& name);
		[[nodiscard]] atomic::UniqueItem& findItemById(const int& assetId);
		[[nodiscard]] ItemContainer itemMatch(const std::function<bool(const atomic::UniqueItem&)>& function);
	};
}

#endif