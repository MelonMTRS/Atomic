#ifndef ATOMIC_BOT_H
#define ATOMIC_BOT_H
#include <tuple>
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
	[[nodiscard]] std::tuple<atomic::Offer, int> makeOffer(const atomic::Inventory& AuthInventory, const atomic::Inventory& VictimInventory, config::Config& config, int tries=0);
	[[nodiscard]] atomic::TradeAction evaluateTrade(rolimons::ItemDB& items, const atomic::Trade& trade, config::Config& config);
	[[nodiscard]] atomic::User findUser(atomic::AuthUser& user, rolimons::ItemDB& items);
}

#endif