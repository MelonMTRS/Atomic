#include <string>
#include "../User.h"
#include "../Inventory.h"
#include "../Offer.h"
#include "../AuthUser.h"
#include "../Trade.h"
#ifndef __ATOMIC__ROBLOX__WRAPPER__H
#define __ATOMIC__ROBLOX__WRAPPER__H

/*
* Wrapper for the Roblox API
*/

namespace roblox {
	// Gets the X-CSRF token
	[[nodiscard]] std::string getToken(const std::string& cookie);
	// Returns an atomic::AuthUser object from the roblosecurity cookie
	[[nodiscard]] atomic::AuthUser getUserFromCookie(std::string cookie);
	// Whether or not the user has premium or not.
	[[nodiscard]] bool isPremium(atomic::AuthUser authuser, atomic::User user);
	// Gets a users inventory
	[[nodiscard]] atomic::Inventory getInventory(atomic::User user);
	// Counters/Sends a trade to a user
	void send_trade(atomic::AuthUser user, atomic::User target, atomic::Offer offer);
	void counter_trade(atomic::AuthUser user, const atomic::Trade& trade, const atomic::Offer& newOffer);
	void cancel_trade(atomic::AuthUser user, const atomic::Trade& trade);
	// Whether or not you can send a trade with that user
	[[nodiscard]] bool can_trade(atomic::AuthUser user, atomic::User target);
	// Gets a trade by tradeId
	[[nodiscard]] atomic::Trade get_trade(atomic::AuthUser& user, int tradeId);
	// Returns an array of inbound/outbound/inactive/completed trades
	// NOTE: This function uses std::async to pool the trades faster
	[[nodiscard]] std::vector<atomic::Trade> get_trades(atomic::TradeType tradeType, atomic::AuthUser user, int limit=25);
}

#endif