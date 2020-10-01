#include <string>
#include <regex>
#include "./Conversion.h"

std::string atomic::formatCookie(std::string cookie) {
	std::regex pattern{R"(_\|[\D\d]+\|_)"};
	return std::regex_replace(cookie, pattern, "");
}