#include <string>
#include "./Trade.h"
#ifndef __ATOMIC__ROBLOX__CONVERSION__H
#define __ATOMIC__ROBLOX__CONVERSION__H

/*
	Used for conversion, and includes some other stuff
*/

namespace atomic {
	// Formats the .roblosecurity cookie (removes the warning message)
	[[nodiscard]] std::string formatCookie(std::string cookie);
	// Converts an atomic::Trade object to JSON
	[[nodiscard]] std::string tradeToJSON(atomic::AuthUser user, atomic::Trade trade);
}

#endif