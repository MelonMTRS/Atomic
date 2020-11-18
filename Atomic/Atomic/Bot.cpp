#include <array>
#include <iostream>
#include "./Config/Parser.h"
#include "./API/Wrapper.h"
#include "./API/Rolimons.h"
#include "./Demand.h"
#include "./Bot.h"
#include "./Functions.h"
#include "./Item.h"
#include "./Exceptions.h"

[[nodiscard]] atomic::TradeAction atomic::evaluateTrade(rolimons::ItemDB& items, const atomic::Trade& trade, const config::Config&) {
	std::int64_t totalOffering = trade.getOffer().getTotalOfferedValue();
	std::int64_t totalRequesting = trade.getOffer().getTotalRequestedValue();
	atomic::Offer offer = trade.getOffer();
	if (totalOffering > totalRequesting) {
		for (auto item = offer.getOffering().begin(); item != offer.getOffering().end(); ++item) {
			if (item->id != 0) {
				if (rolimons::isProjected(items, item->id))
					return atomic::TradeAction::Decline;
			}
		}
		for (auto item = offer.getOffering().begin(); item != offer.getOffering().end(); ++item) {
			if (computational::getPercent(atomic::getAveragePrice(*item), static_cast<double>(item->rap)) < 35) {
				// Probably a projected and rolimons hasn't caught on to it yet
				return atomic::TradeAction::Decline;
			}
		}
		return atomic::TradeAction::Accept;
	}
	else {
		return atomic::TradeAction::Decline;
	}
	return atomic::TradeAction::Ignore;
}

[[nodiscard]] atomic::User atomic::findUser(atomic::AuthUser& user, rolimons::ItemDB& items) {
	int method = atomic::random(1, 5) == 1 ? 2 : 1;
	if (method == 1) {
		// Limited Item Resellers
		atomic::Item randomItem = rolimons::getRandomItem(items);
		while (randomItem.demand == atomic::Demand::Terrible) {
			randomItem = rolimons::getRandomItem(items);
		}
		std::vector<atomic::User> resellers = roblox::getResellers(user, randomItem);
		int tries = 0;
		while (tries <= 25) {
			tries++;
			const atomic::User& randomUser = atomic::random_choice(resellers);
			if (user.canTradeWith(randomUser))
				return randomUser;
		}
		return atomic::findUser(user, items);
	}
	else if (method == 2) {
		// Group User Searching
		constexpr std::array<int, 3> focusedRoles = { 21783158, 36901726, 3843519 };
		const int randomRole = focusedRoles[atomic::random(0, focusedRoles.size()-1)];
		std::vector<atomic::User> users = roblox::getUsersInGroup(650266, randomRole);
		int tries = 0;
		while (tries <= 25) {
			tries++;
			const atomic::User& randomUser = atomic::random_choice(users);
			if (user.canTradeWith(randomUser))
				return randomUser;
		}
		return atomic::findUser(user, items); // If it couldn't find anything, then try again until it does.
	}
	else if (method == 3) {
		// TODO: Search through the authenticated user's inactive/completed trades
		// If user does not have any or barely has any, mark it in cache so this method is not used again
	}
	return atomic::findUser(user, items);
}