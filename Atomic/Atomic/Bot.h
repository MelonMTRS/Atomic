#ifndef __ATOMIC__BOT__H
#define __ATOMIC__BOT__H
#include "./Offer.h"
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
	[[nodiscard]] atomic::Offer makeOffer(const atomic::Inventory& AuthInventory, const atomic::Inventory& VictimInventory);
	[[nodiscard]] atomic::TradeAction evaluateTrade(atomic::Trade& trade);
}

#endif