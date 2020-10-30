#ifndef ATOMIC_CONFIGPARSER_PARSER_H
#define ATOMIC_CONFIGPARSER_PARSER_H
#include <iostream>
#include <vector>
#include <map>
#include <variant> // C++17

// TODO: Improve this entire system

namespace config {
	class Config {
	private:
		std::string m_filename;
		std::map<std::string, std::string> m_data;
	public:
		Config() = default;
		Config(std::string filename);

		int getInt(std::string key);
		int64_t getInt64(std::string key);
		bool getBool(std::string key);
		std::string getString(std::string key);
	};
}

#endif