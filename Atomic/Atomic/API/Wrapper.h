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
* All functionality here uses Atomic's classes
* Non-async
*/

namespace roblox {
	// Gets the X-CSRF token
	[[nodiscard]] std::string getToken(const std::string& cookie);
	// Returns an atomic::AuthUser object from the roblosecurity cookie
	[[nodiscard]] atomic::AuthUser getUserFromCookie(std::string cookie);
	// Gets a users inventory
	[[nodiscard]] atomic::Inventory getInventory(atomic::User user);
	// Counters/Sends a trade to a user
	void send_trade(atomic::AuthUser user, atomic::User target, atomic::Offer offer);
	void counter_trade(atomic::AuthUser user, const atomic::Trade& trade, const atomic::Offer& newOffer);
	void cancel_trade(atomic::AuthUser user, const atomic::Trade& trade);
	// Whether or not you can send a trade with that user
	[[nodiscard]] bool can_trade(atomic::AuthUser user, atomic::User target);
	// Gets a trade by tradeId
	[[nodiscard]] atomic::Trade get_trade(atomic::AuthUser user, int tradeId);
}

#endif