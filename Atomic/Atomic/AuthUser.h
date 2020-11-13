#ifndef ATOMIC_AUTHUSER_H
#define ATOMIC_AUTHUSER_H
#include <string>
#include "./API/Rolimons.h"
#include "./Inventory.h"
#include "./User.h"

namespace atomic {
	class AuthUser {
	private:
		std::string m_name;
		std::string m_cookie;
		std::string m_xcsrf;
		int m_id;
	public:
		AuthUser() = default;
		AuthUser(const std::string& name, const std::string& xcsrf, const std::string& cookie, const int& id)
			: m_name{ name }, m_xcsrf{ xcsrf }, m_cookie{ cookie }, m_id{ id }
		{
		}

		inline void setCookie(const std::string& newCookie) noexcept { this->m_cookie = newCookie; }
		[[nodiscard]] inline const atomic::User getUser() const noexcept { return atomic::User{ this->m_id, this->m_name }; };
		[[nodiscard]] inline const std::string name() const noexcept { return this->m_name; }
		[[nodiscard]] inline const std::string getCookie() const noexcept { return this->m_cookie; }
		[[nodiscard]] inline const std::string getXcsrf() const noexcept { return this->m_xcsrf; }
		[[nodiscard]] inline const int getId() const noexcept { return this->m_id; }
		[[nodiscard]] atomic::Inventory getInventory(rolimons::ItemDB& items);
		[[nodiscard]] const bool canTradeWith(const atomic::User& user) const;
		[[nodiscard]] const bool isPremium() const;
	};
}

#endif