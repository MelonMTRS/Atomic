#ifndef __ATOMIC__INVENTORY__H
#define __ATOMIC__INVENTORY__H
#include <vector>
#include "./Item.h"

namespace atomic {
	using ItemContainer = std::vector<atomic::Item>;
	class Inventory {
	private:
		ItemContainer m_inventory;
	public:
		Inventory() = default;
		Inventory(ItemContainer inventory)
			: m_inventory{inventory}
		{
		}

		inline const void addItem(const atomic::Item item) { this->m_inventory.push_back(item); }
		[[nodiscard]] inline const ItemContainer& getInventory() const noexcept { return this->m_inventory; }

		atomic::Item& operator[](int index) { return this->m_inventory[index]; }

		ItemContainer::iterator begin() { return this->m_inventory.begin(); }
		ItemContainer::iterator end() { return this->m_inventory.end(); }
	};
}

#endif