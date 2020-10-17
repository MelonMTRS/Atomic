#ifndef __ATOMIC__AUTHUSER__H
#define __ATOMIC__AUTHUSER__H
#include <string>
#include <iostream>
#include "./Inventory.h"
#include "./API/Rolimons.h"

namespace atomic {
	class AuthUser {
	private:
		std::string m_name;
		std::string m_cookie;
		std::string m_xcsrf;
		int m_id;
	public:
		AuthUser(std::string name, std::string xcsrf, std::string cookie, int id)
			: m_name{ name }, m_xcsrf{ xcsrf }, m_cookie{ cookie }, m_id{ id }
		{
		}

		inline void setCookie(std::string newCookie) noexcept { this->m_cookie = newCookie; }
		[[nodiscard]] inline const std::string getName() const noexcept { return this->m_name; }
		[[nodiscard]] inline const std::string getCookie() const noexcept { return this->m_cookie; }
		[[nodiscard]] inline const std::string getXcsrf() const noexcept { return this->m_xcsrf; }
		[[nodiscard]] inline const int getId() const noexcept { return this->m_id; }
		atomic::Inventory getInventory(rolimons::ItemDB& items);
	};
}

#endif