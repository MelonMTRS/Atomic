#include <vector>
#include "./Item.h"
#ifndef __ATOMIC__INVENTORY__H
#define __ATOMIC__INVENTORY__H

namespace atomic {
	using InventoryObj = std::vector<atomic::Item>;
	class Inventory {
		/*
		Represents a users Inventory object
		*/
	private:
		InventoryObj m_inventory;
	public:
		template <typename _Array>
		Inventory(_Array inventory)
			: m_inventory{inventory}
		{
		}

		inline void addItem(const atomic::Item item) { this->m_inventory.push_back(item); }
		inline InventoryObj getInventory() { return this->m_inventory; }
	};
}

#endif