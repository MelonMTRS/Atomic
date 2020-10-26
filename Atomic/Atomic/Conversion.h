#ifndef ATOMIC_CONVERSION_H
#define ATOMIC_CONVERSION_H
#include <string>
#include "./User.h"
#include "./Trade.h"
#include "./AuthUser.h"

/*
	Used for conversion, and includes some other stuff
*/

namespace atomic {
	[[nodiscard]] std::string formatCookie(const std::string& cookie);
	[[nodiscard]] std::string tradeToJSON(const atomic::AuthUser& user, const atomic::Trade& trade);
}

#endif