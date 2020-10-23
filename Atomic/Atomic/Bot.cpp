#include <array>
#include "./API/Wrapper.h"
#include "./API/Rolimons.h"
#include "./Bot.h"
#include "./Functions.h"
#include "./Item.h"
#include "./Exceptions.h"

atomic::TradeAction atomic::evaluateTrade(atomic::Trade& trade) {
	if (trade.getTradeType() == atomic::TradeType::Inbound) {
		// TODO: Evaluation here
	}
	return atomic::TradeAction::Ignore; // Temporarily to avoid errors
}

atomic::User atomic::findUser(atomic::AuthUser user, rolimons::ItemDB& items) {
	int method = atomic::random(1, 1); // Methods of searching for a user, chosen by random.
	if (method == 1) {
		// Limited Item Resellers
		atomic::Item randomItem = rolimons::getRandomItem(items);
		while (randomItem.demand == atomic::Demand::Terrible || randomItem.demand == atomic::Demand::Low) {
			randomItem = rolimons::getRandomItem(items);
		}
		std::vector<atomic::User> resellers = roblox::getResellers(user, randomItem);
		for (auto reseller = resellers.begin(); reseller != resellers.end(); ++reseller) {
			if (roblox::can_trade(user, *reseller)) {
				return *reseller;
			}
		}
	}
	else if (method == 2) {
		// Group User Searching
		std::array<int, 0U> groups = {}; // TODO: Add trading groups here
	}
}