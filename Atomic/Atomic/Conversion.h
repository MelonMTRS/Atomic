#ifndef ATOMIC_CONVERSION_H
#define ATOMIC_CONVERSION_H
#include <string>
#include "./User.h"
#include "./Trade.h"
#include "./AuthUser.h"

namespace atomic {
	[[nodiscard]] std::string formatCookie(const std::string& cookie);
	[[nodiscard]] std::string tradeToJSON(const atomic::AuthUser& user, const atomic::Trade& trade);
}

#endif