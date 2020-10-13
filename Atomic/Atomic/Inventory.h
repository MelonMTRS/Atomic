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
		template <typename _Array>
		Inventory(_Array inventory)
			: m_inventory{inventory}
		{
		}

		inline const void addItem(const atomic::Item item) { this->m_inventory.push_back(item); }
		[[nodiscard]] inline const ItemContainer& getInventory() const noexcept { return this->m_inventory; }
	};
}

#endif