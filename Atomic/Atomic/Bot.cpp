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
	int method = atomic::random(1, 2);
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
		return atomic::findUser(user, items);
	}
	else if (method == 2) {
		// Group User Searching
		int tradingGroup = { 650266 };
		std::array<int, 3> focusedRoles = { 21783158, 36901726, 3843519 }; // RoleIds to focus on
		int& randomRole = focusedRoles[atomic::random(0, focusedRoles.size()-1)];
		std::vector<atomic::User>& users = roblox::getUsersInGroup(tradingGroup, randomRole);
		while (true) {
			atomic::User& randomUser = users[atomic::random(0, users.size() - 1)];
			if (roblox::can_trade(user, randomUser))
				return randomUser;
		}
		return atomic::findUser(user, items); // If it couldn't find anything, then try again until it does.
	}
}