#include "./atomic.h"
#ifndef __ATOMIC__BOT__H
#define __ATOMIC__BOT__H

/*
* Algorithmic functions
*/

namespace atomic {
	// Takes the authenticated users inventory and the victims inventory, then returns an offer.
	atomic::Offer makeOffer(const atomic::Inventory& AuthInventory, const atomic::Inventory& VictimInventory);
	// Evaluates a trade, returns true if the trade should be accepted, false if not.
	bool evaluateTrade(const atomic::Trade& trade);
}

#endif