#define _SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING
#include <filesystem>
#include <fstream>
#include "../Exceptions.h"
#include "../Functions.h"
#include "./Config.h"
#include "./Parser.h"
#include "./cpr/cpr.h"

namespace fs = std::filesystem;

bool config::configExists() {
	fs::path expectedPath = fs::current_path() / fs::path("config.cfg");
	return fs::is_regular_file(expectedPath);
}

std::string config::getDefaultConfig() {
	cpr::Response defaultConfig = cpr::Get(cpr::Url{ "https://raw.githubusercontent.com/viown/Atomic/master/Data/DefaultConfig.cfg" });
	if (!atomic::isStatusSuccess(defaultConfig.status_code))
		throw atomic::HttpError{ "ConfigFetchFailure", defaultConfig.status_code };
	return defaultConfig.text;
}

void config::createConfig(std::string configData) {
	std::ofstream config{"config.cfg"};
	if (!config)
		throw atomic::ConfigLoadFailure{"Failed to create"};
	config << configData;
	config.close();
}