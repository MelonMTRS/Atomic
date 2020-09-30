#include <string>
#include "Inventory.h"
#ifndef __ATOMIC__USER__H
#define __ATOMIC__USER__H

namespace atomic {
	class User {
	private:
		int m_id;
	public:
		User(int id, bool confirmExistence=false)
			: m_id{ id }
		{
			if (confirmExistence) {
				// TODO: Confirm if User does exist
			}
		}

		atomic::Inventory getInventory();
		void send_trade();
	};
}

#endif