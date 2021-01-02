#ifndef ATOMIC_CONFIG_CONFIG_H
#define ATOMIC_CONFIG_CONFIG_H
#include <string>
#include <tuple>
#include "./Parser.h"

namespace config {
	bool configExists();
	std::tuple<bool, std::string> validateConfig(config::Config config) noexcept;
	std::string getDefaultConfig();
	void createConfig(const std::string& configData);
}

#endif