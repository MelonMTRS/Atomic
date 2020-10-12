#include "./Conversion.h"
#include <string>
#include <iostream>
#ifndef __ATOMIC__AUTHUSER__H
#define __ATOMIC__AUTHUSER__H

namespace atomic {
	class AuthUser {
		/*
		Represents the authenticated user
		*/
	private:
		const std::string m_name;
		const std::string m_cookie;
		const int m_id;
	public:
		AuthUser(std::string name, std::string cookie, int id)
			: m_name{ name }, m_cookie{ atomic::formatCookie(cookie) }, m_id{ id }
		{
		}


		[[nodiscard]] inline const std::string getName() const noexcept { return this->m_name; }
		[[nodiscard]] inline const std::string getCookie() const noexcept { return this->m_cookie; }
		[[nodiscard]] inline const int getId() const noexcept { return this->m_id; }
		//atomic::Inventory getInventory();
	};
}

#endif