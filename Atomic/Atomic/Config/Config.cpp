#include <filesystem>
#include "./Config.h"
#include "./Parser.h"

namespace fs = std::filesystem;

bool config::configExists() {
	fs::path expectedPath = fs::current_path() / fs::path("config.cfg");
	return fs::is_regular_file(expectedPath);
}