#include <filesystem>
#include <fstream>
#include "../Functions.h"
#include "../Exceptions.h"
#include "./Config.h"
#include "./cpr/cpr.h"
#include "./Parser.h"

namespace fs = std::filesystem;

bool config::configExists() {
	fs::path expectedPath = fs::current_path() / fs::path("config.cfg");
	return fs::is_regular_file(expectedPath);
}

std::string config::getDefaultConfig() {
	// Temporarily using gists, when source is public use: https://github.com/viown/Atomic/blob/master/Data/DefaultConfig.cfg
	cpr::Response defaultConfig = cpr::Get(cpr::Url{ "https://gist.githubusercontent.com/viown/3c59e04dc82cdf07fce52e0b4a10b020/raw/8386f8f00bae4865438b6d578451012e76da4575/config.cfg" });
	if (!atomic::isStatusSuccess(defaultConfig.status_code))
		throw atomic::HttpError{ "ConfigFetchFailure", defaultConfig.status_code };
	return defaultConfig.text;
}

void config::createConfig(std::string configData) {
	std::ofstream config{"config.cfg"};
	if (!config)
		throw atomic::ConfigLoadFailure{"Failed to create"};
	config << configData;
}