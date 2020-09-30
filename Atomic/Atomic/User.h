#include <string>
#ifndef __ATOMIC__USER__H
#define __ATOMIC__USER__H

namespace atomic {
	class User {
	private:
		std::string m_name;
		int m_id;
	public:
		User(std::string name, int id)
			: m_name{ name }, m_id{ id }
		{

		}
	};
}

#endif