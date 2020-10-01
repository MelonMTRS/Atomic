#include "./atomic.h"
#ifndef __ATOMIC__BOT__H
#define __ATOMIC__BOT__H

namespace atomic {
	// Takes the authenticated users inventory and the victims inventory, then returns an offer.
	atomic::Offer makeOffer(atomic::Inventory AuthInventory, atomic::Inventory VictimInventory);
}

#endif