#ifndef ATOMIC_USER_H
#define ATOMIC_USER_H
#include <string>
#include "./API/Rolimons.h"

#define USER_DEFAULT {0}

namespace atomic {
	class User {
	private:
		std::int64_t m_id;
		std::string m_name;
	public:
		User() = default;
		User(const std::int64_t& id, const std::string& name="None")
			: m_id{ id }, m_name{ name }
		{
		}

		[[nodiscard]] const std::int64_t getId() const noexcept { return this->m_id; }
		[[nodiscard]] const std::string name() const noexcept { return this->m_name; }
		[[nodiscard]] atomic::Inventory getInventory(rolimons::ItemDB& items) const noexcept {
			return rolimons::getUser(items, this->getId()).inventory;
		}
		atomic::User& operator=(const atomic::User& user) {
			this->m_id = user.m_id;
			this->m_name = user.m_name;
			return *this;
		}
	};
}

#endif