#include <string>
#include "./Inventory.h"
#ifndef __ATOMIC__USER__H
#define __ATOMIC__USER__H

namespace atomic {
	class User {
	private:
		const int m_id;
		std::string m_username = "__NOTSET";
	public:
		User(int id, bool confirmExistence=false)
			: m_id{ id }
		{
			if (confirmExistence) {
				// TODO: Confirm if User does exist
			}
		}

		int getId() { return this->m_id; }
		std::string getUsername() { return this->m_username; }
		atomic::Inventory getInventory();
		void send_trade();
	};
}

#endif