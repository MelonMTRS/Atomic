#ifndef __ATOMIC__CONFIGPARSER__PARSER__H
#define __ATOMIC__CONFIGPARSER__PARSER__H
#include <string>
#include <map>

namespace atomic {
	struct KeyNotFound {
		std::string error_message;
	};
}

namespace config {
	class Config {
	private:
		std::string m_fileName;
	public:
		Config(std::string fileName) :
			m_fileName{ fileName }
		{
			// TODO: Parsing here
		}

		// Returns the value indexed, throws an atomic::KeyNotFound if key does not exist
		std::string operator[](std::string index) {
			// TODO: basically everything
		}
	};
}

#endif