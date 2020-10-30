#ifndef ATOMIC_CONFIGPARSER_PARSER_H
#define ATOMIC_CONFIGPARSER_PARSER_H
#include <map>

namespace config {
	class Config {
	private:
		std::string m_filename;
		std::map<std::string, std::string> m_data;
	public:
		Config() = default;
		Config(const std::string& filename);

		int const getInt(const std::string& key);
		int64_t const getInt64(const std::string& key);
		bool const getBool(const std::string& key);
		std::string const getString(const std::string& key);
	};
}

#endif