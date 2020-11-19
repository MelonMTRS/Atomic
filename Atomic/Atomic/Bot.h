#ifndef ATOMIC_BOT_H
#define ATOMIC_BOT_H
#include "./AuthUser.h"
#include "./Config/Parser.h"
#include "./Inventory.h"
#include "./Offer.h"
#include "./Trade.h"

namespace atomic {
	enum class TradeAction {
		Accept,
		Decline,
		Counter,
		Ignore
	};
	[[nodiscard]] atomic::Offer makeOffer(atomic::Inventory& AuthInventory, atomic::Inventory& VictimInventory);
	[[nodiscard]] atomic::TradeAction evaluateTrade(rolimons::ItemDB& items, const atomic::Trade& trade, const config::Config&);
	[[nodiscard]] atomic::User findUser(atomic::AuthUser& user, rolimons::ItemDB& items);
}

#endif