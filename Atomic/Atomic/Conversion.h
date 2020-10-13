#ifndef __ATOMIC__CONVERSION__H
#define __ATOMIC__CONVERSION__H
#include <string>
#include "./User.h"
#include "./Trade.h"
#include "./AuthUser.h"

/*
	Used for conversion, and includes some other stuff
*/

namespace atomic {
	// Formats the .roblosecurity cookie (removes the warning message)
	// All cookies should be formatted before used
	[[nodiscard]] std::string formatCookie(std::string cookie);
	// Converts an atomic::Trade object to roblox sendable JSON
	[[nodiscard]] std::string tradeToJSON(atomic::AuthUser user, atomic::Trade trade);
}

#endif