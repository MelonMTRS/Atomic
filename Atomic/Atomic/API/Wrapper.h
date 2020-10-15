#ifndef __ATOMIC__ROBLOX__WRAPPER__H
#define __ATOMIC__ROBLOX__WRAPPER__H
#include <string>
#include "../User.h"
#include "../Inventory.h"
#include "../Offer.h"
#include "../AuthUser.h"
#include "../Trade.h"

/*
* Wrapper for the Roblox API
*/

namespace roblox {
	enum class Membership { // Roblox memberships
		Normal,
		Premium
	};

	enum class TradeResult {
		Success,
		Failure
	};

	// Gets the X-CSRF token
	[[nodiscard]] std::string getToken(const std::string& cookie);
	// Returns an atomic::AuthUser object from the roblosecurity cookie
	[[nodiscard]] atomic::AuthUser getUserFromCookie(std::string cookie);
	// Whether or not the user has premium or not.
	[[nodiscard]] roblox::Membership getMembership(atomic::AuthUser authuser, atomic::User user);
	// Gets a users inventory
	[[nodiscard]] atomic::Inventory getInventory(atomic::User user);
	// Sends a trade to a user
	// Returns a TradeResult::Success if the trade was successfully sent
	roblox::TradeResult sendTrade(atomic::AuthUser user, atomic::Trade trade);
	// Counters an already existing trade, a new offer object must be passed
	// Returns a TradeResult::Success if the trade was successfully countered
	roblox::TradeResult counterTrade(atomic::AuthUser user, const atomic::Trade& trade, const atomic::Offer& newOffer);
	// Declines an already existing trade
	// Returns a TradeResult::Success if the trade was successfully declined
	roblox::TradeResult declineTrade(atomic::AuthUser user, const atomic::Trade& trade);
	// Whether or not you can send a trade with that user
	[[nodiscard]] bool can_trade(atomic::AuthUser user, atomic::User target);
	// Gets a trade by tradeId
	[[nodiscard]] atomic::Trade getTrade(atomic::AuthUser& user, int tradeId);
	// Returns an array of inbound/outbound/inactive/completed trades
	// NOTE: This function uses std::async to pool the trades faster
	[[nodiscard]] std::vector<atomic::Trade> getTrades(atomic::AuthUser user, atomic::TradeType tradeType, int limit=25);
}

#endif