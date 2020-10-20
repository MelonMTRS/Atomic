#ifndef __ATOMIC__CONFIGPARSER__PARSER__H
#define __ATOMIC__CONFIGPARSER__PARSER__H
#include <iostream>
#include <vector>
#include <map>
#include <variant> // C++17

namespace config {
	using Parser = std::map<std::string, std::string>;
	using ParseValue = std::variant<int, bool, std::string>;
	config::Parser parse(std::string filename);
	ParseValue get(config::Parser ParseObject, std::string key);
}

#endif