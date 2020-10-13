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
	[[nodiscard]] std::string formatCookie(std::string cookie);
	// Converts an atomic::Trade object to JSON
	[[nodiscard]] std::string tradeToJSON(atomic::AuthUser& user, atomic::Trade trade);
}

#endif