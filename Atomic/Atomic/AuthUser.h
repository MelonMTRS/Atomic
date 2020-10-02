#include "./atomic.h"
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
		std::string m_name;
		std::string m_cookie;
		int m_id;
	public:
		AuthUser(std::string name, std::string cookie, int id)
			: m_name{ name }, m_cookie{atomic::formatCookie(cookie)}, m_id{ id }
		{
		}
		inline std::string getName() { return this->m_name; }
		inline std::string getCookie() { return this->m_cookie; }
		inline int getId() { return this->m_id; }
		atomic::Inventory getInventory();
	};
}

#endif