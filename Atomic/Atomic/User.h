#ifndef __ATOMIC__USER__H
#define __ATOMIC__USER__H
#include <string>
#include "./Inventory.h"

namespace atomic {
	class User {
	private:
		const std::int64_t m_id;
	public:
		User(std::int64_t id, bool confirmExistence=false)
			: m_id{ id }
		{
			if (confirmExistence) {
				// TODO: Confirm if User does exist
			}
		}

		[[nodiscard]] const int getId() const noexcept { return this->m_id; }
		[[nodiscard]] atomic::Inventory getInventory() const noexcept;
		void send_trade() const;
	};
}

#endif