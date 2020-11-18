#ifndef ATOMIC_USER_H
#define ATOMIC_USER_H
#include <string>
#include "./API/Rolimons.h"
#include "./Inventory.h"

namespace atomic {
	class User {
	private:
		const std::int64_t m_id;
		const std::string m_name;
	public:
		User(const std::int64_t& id, const std::string& name="None")
			: m_id{ id }, m_name{ name }
		{
		}

		[[nodiscard]] const std::int64_t getId() const noexcept { return this->m_id; }
		[[nodiscard]] const std::string name() const noexcept { return this->m_name; }
		[[nodiscard]] atomic::Inventory getInventory(rolimons::ItemDB& items) const noexcept {
			return rolimons::getUser(items, this->getId()).inventory;
		}
		[[nodiscard]] atomic::Inventory getRobloxInventory(rolimons::ItemDB& items) const noexcept {
			return roblox::getInventory(*this, items);
		}
		void send_trade() const;
	};
}

#endif