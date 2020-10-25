#ifndef __ATOMIC__USER__H
#define __ATOMIC__USER__H
#include <string>
#include "./API/Rolimons.h"
#include "./Inventory.h"

namespace atomic {
	class User {
	private:
		const std::int64_t m_id;
		const std::string m_name;
	public:
		User(const std::int64_t& id, const std::string& name="None", const bool& confirmExistence=false)
			: m_id{ id }, m_name{ name }
		{
			if (confirmExistence) {
				// TODO: Confirm if User does exist
			}
		}

		[[nodiscard]] const int getId() const noexcept { return this->m_id; }
		[[nodiscard]] const std::string name() const noexcept { return this->m_name; }
		[[nodiscard]] atomic::Inventory getInventory(rolimons::ItemDB& items) const noexcept;
		void send_trade() const;
	};
}

#endif