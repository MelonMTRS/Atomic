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
	std::string getToken(std::string cookie);
	// Returns an atomic::AuthUser object from the roblosecurity cookie
	atomic::AuthUser getUserFromCookie(std::string cookie);
	// Gets a users inventory
	atomic::Inventory getInventory(atomic::User user);
	// Counters/Sends a trade to a user
	void send_trade(atomic::AuthUser user, atomic::User target, atomic::Offer offer);
	void counter_trade(atomic::AuthUser user, atomic::User target, atomic::Offer newOffer);
	// Whether or not you can send a trade with that user
	bool can_trade(atomic::AuthUser user, atomic::User target);
	// Gets a trade by tradeId
	atomic::Trade get_trade(int tradeId);
}

#endif