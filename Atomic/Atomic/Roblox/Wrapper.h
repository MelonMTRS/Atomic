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
*/

namespace roblox {
	// Gets the users Id from the roblosecurity cookie
	int getIdFromCookie(std::string cookie);
	// Gets a users inventory
	atomic::Inventory getInventory(atomic::User user);
	// Sends a trade to a user
	void send_trade(atomic::AuthUser user, atomic::User target, atomic::Offer offer);
	// Whether or not you can send a trade with that user
	bool can_trade(atomic::AuthUser user, atomic::User target);
	// Gets a trade by tradeId
	atomic::Trade get_trade(int tradeId);
}

#endif