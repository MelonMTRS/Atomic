#ifndef ATOMIC_BOT_H
#define ATOMIC_BOT_H
#include "./Offer.h"
#include "./AuthUser.h"
#include "./Inventory.h"
#include "./Trade.h"

namespace atomic {
	enum class TradeAction {
		Accept,
		Decline,
		Counter,
		Ignore
	};
	[[nodiscard]] atomic::Offer makeOffer(atomic::Inventory& AuthInventory, atomic::Inventory& VictimInventory);
	[[nodiscard]] atomic::TradeAction evaluateTrade(rolimons::ItemDB& items, const atomic::Trade& trade);
	[[nodiscard]] atomic::User findUser(atomic::AuthUser& user, rolimons::ItemDB& items);
}

#endif