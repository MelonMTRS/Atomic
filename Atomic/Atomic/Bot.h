#ifndef ATOMIC_BOT_H
#define ATOMIC_BOT_H
#include "./Offer.h"
#include "./AuthUser.h"
#include "./Inventory.h"
#include "./Trade.h"

// Trades above this rap will return atomic::TradeAction::Ignore
#define TOTAL_ACCEPTED_RAP 4500

/*
* Algorithmic functions
*/

namespace atomic {
	enum class TradeAction {
		Accept,
		Decline,
		Ignore
	};
	[[nodiscard]] atomic::Offer makeOffer(atomic::Inventory& AuthInventory, atomic::Inventory& VictimInventory);
	[[nodiscard]] atomic::TradeAction evaluateTrade(atomic::Trade& trade);
	[[nodiscard]] atomic::User findUser(atomic::AuthUser user, rolimons::ItemDB& items, int maxRange=2); // Returns a random user to trade with
}

#endif