#include "./atomic.h"
#ifndef __ATOMIC__BOT__H
#define __ATOMIC__BOT__H

/*
* Algorithmic functions
*/

namespace atomic {
	enum class TradeAction {
		Accept,
		Cancel,
		Ignore
	};
	// Takes the authenticated users inventory and the victims inventory, then returns an offer.
	[[nodiscard]] atomic::Offer makeOffer(const atomic::Inventory& AuthInventory, const atomic::Inventory& VictimInventory);
	// Evaluates a trade, returns TradeAction::Accept if the trade should be accepted, TradeAction::Cancel if not. Trade must be inbound
	// Important note: This function returns TradeAction::Ignore on trades above 5k rap
	[[nodiscard]] atomic::TradeAction evaluateTrade(atomic::Trade& trade);
}

#endif