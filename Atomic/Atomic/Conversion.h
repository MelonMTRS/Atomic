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
	[[nodiscard]] std::string formatCookie(const std::string& cookie);
	[[nodiscard]] std::string tradeToJSON(atomic::AuthUser user, atomic::Trade trade);
}

#endif