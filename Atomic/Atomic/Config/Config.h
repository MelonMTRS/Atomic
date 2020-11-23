#ifndef ATOMIC_CONFIG_CONFIG_H
#define ATOMIC_CONFIG_CONFIG_H
#include <string>
#include "./Parser.h"

namespace config {
	bool configExists();
	bool validateConfig(config::Config config);
	std::string getDefaultConfig();
	void createConfig(std::string configData);
}

#endif