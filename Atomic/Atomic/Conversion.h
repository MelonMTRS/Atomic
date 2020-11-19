#ifndef ATOMIC_CONVERSION_H
#define ATOMIC_CONVERSION_H
#include <string>
#include "./AuthUser.h"
#include "./Trade.h"
#include "./User.h"

namespace atomic {
	[[nodiscard]] std::string formatCookie(const std::string& cookie);
	[[nodiscard]] std::string tradeToJSON(const atomic::AuthUser& user, const atomic::Trade& trade);
}

#endif