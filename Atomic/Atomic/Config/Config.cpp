#define _SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING
#include <filesystem>
#include <fstream>
#include <tuple>
#include "../Exceptions.h"
#include "../Functions.h"
#include "./Config.h"
#include "./Parser.h"
#include "./cpr/cpr.h"

namespace fs = std::filesystem;

bool isnums(const std::string& str) noexcept {
	for (char c : str) {
		if (!std::isdigit(c))
			return false;
	}
	return true;
}

bool config::configExists() {
	fs::path expectedPath = fs::current_path() / fs::path("config.cfg");
	return fs::is_regular_file(expectedPath);
}

std::tuple<bool, std::string> config::validateConfig(config::Config config) noexcept {
	if (std::string os = atomic::lower(config.getString("operating_system")); os != "linux" && os != "windows")
		return std::make_tuple(false, "Config value for `operating_system` set to unknown value '" + os + "'");
	else if (!isnums(config.getString("update_values")))
		return std::make_tuple(false, "Config value for `update_values` set to invalid characters '" + config.getString("update_values") + "'");
	else if (!isnums(config.getString("time_between_trade")))
		return std::make_tuple(false, "Config value for `time_between_trade` set to invalid characters '" + config.getString("time_between_trade") + "'");
	else if (!isnums(config.getString("max_item_value")))
		return std::make_tuple(false, "Config value for `max_item_value` set to invalid characters '" + config.getString("max_item_value") + "'");
	else if (!isnums(config.getString("minimum_profit")))
		return std::make_tuple(false, "Config value for `minimum_profit` set to invalid characters '" + config.getString("minimum_profit") + "'");
	else if (atomic::split(config.getString("maximum_items_to_trade"), '/').size() != 2)
		return std::make_tuple(false, "Config value for `minimum_items_trade` set to unknown value '" + config.getString("maximum_items_to_trade") + "'");
	else if (std::string check_inbound = config.getString("check_inbound_trades"); check_inbound != "true" && check_inbound != "false")
		return std::make_tuple(false, "Config value for `check_inbound_trades` set to unknown value '" + check_inbound + "', must be true/false");
	else if (!isnums(config.getString("time_between_check")))
		return std::make_tuple(false, "Config value for `time_between_check` set to invalid characters '" + config.getString("time_between_check") + "'");
	else if (!isnums(config.getString("ignore_trades_above")))
		return std::make_tuple(false, "Config value for `ignore_trades_above` set to invalid characters '" + config.getString("ignore_trades_above") + "'");
	else if (std::string counter_bad_trades = config.getString("counter_bad_trades"); counter_bad_trades != "true" && counter_bad_trades != "false")
		return std::make_tuple(false, "Config value for `check_inbound_trades` set to unknown value '" + check_inbound + "', must be true/false");
	return std::make_tuple(true, ":D");
}

std::string config::getDefaultConfig() {
	cpr::Response defaultConfig = cpr::Get(cpr::Url{ "https://raw.githubusercontent.com/viown/Atomic/master/Data/DefaultConfig.cfg" });
	if (!atomic::isStatusSuccess(defaultConfig.status_code))
		throw atomic::HttpError{ "Failed to fetch config data", defaultConfig.status_code };
	return defaultConfig.text;
}

void config::createConfig(std::string configData) {
	std::ofstream config{"config.cfg"};
	if (!config)
		throw atomic::ConfigLoadFailure{"Failed to create"};
	config << configData;
	config.close();
}