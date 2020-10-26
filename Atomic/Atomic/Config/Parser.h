#ifndef ATOMIC_CONFIGPARSER_PARSER_H
#define ATOMIC_CONFIGPARSER_PARSER_H
#include <iostream>
#include <vector>
#include <map>
#include <variant> // C++17

// TODO: Improve this entire system

namespace config {
	using Parser = std::map<std::string, std::string>;
	using ParseValue = std::variant<int, bool, std::string>;
	config::Parser parse(std::string filename);
	ParseValue get(config::Parser ParseObject, std::string key);
}

#endif