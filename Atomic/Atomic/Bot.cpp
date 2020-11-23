#include <array>
#include <algorithm>
#include <iostream>
#include "./API/Rolimons.h"
#include "./API/Wrapper.h"
#include "./Bot.h"
#include "./Config/Parser.h"
#include "./Demand.h"
#include "./Exceptions.h"
#include "./Functions.h"
#include "./Item.h"
#include "./Offer.h"

[[nodiscard]] atomic::TradeAction atomic::evaluateTrade(rolimons::ItemDB& items, const atomic::Trade& trade, config::Config& config) {
	/*
		TODO: restructure this entire function to follow the dependency ratio with a starter base of 0.5
		greater than 1 = accept
		less than 1 = decline
		-1 = ignore
	*/
	std::int64_t totalOffering = trade.getOffer().getTotalOfferedValue();
	std::int64_t totalRequesting = trade.getOffer().getTotalRequestedValue();
	atomic::Offer offer = trade.getOffer();
	if (offer.getRobuxOffered() != 0 || offer.getRobuxRequested() != 0)
		return atomic::TradeAction::Ignore;
	if (totalOffering > totalRequesting) {
		for (auto item = offer.getOffering().begin(); item != offer.getOffering().end(); ++item) {
			if (item->id != 0) {
				if (rolimons::isProjected(items, item->id))
					return atomic::TradeAction::Decline;
				atomic::Demand itemDemand = item->demand;
				if (itemDemand == atomic::Demand::NotAssigned) {
					itemDemand = atomic::getItemDemand(*item);
					rolimons::setItemDemand(items, item->id, itemDemand);
				}
				if (itemDemand == atomic::Demand::Terrible)
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

template<typename Num, typename Lowest, typename Highest>
[[nodiscard]] constexpr Highest clamp(Num num, Lowest lowest, Highest highest) {
	if (num < lowest)
		return lowest;
	else if (num > highest)
		return highest;
	else
		return num;
}

[[nodiscard]] atomic::Offer atomic::makeOffer(const atomic::Inventory& AuthInventory, const atomic::Inventory& VictimInventory, config::Config& config) {
	if (AuthInventory.item_count() == 0)
		atomic::throwException("You do not have any limited items, cannot create trades.");
	if (VictimInventory.item_count() == 0)
		throw atomic::TradeFormFailure{atomic::TradeErrorTypes::USER_HAS_NO_ITEMS};
	atomic::OfferHolder offering{};
	atomic::OfferHolder requesting{};
	int offeringCursor = 0;
	int requestingCursor = 0;
	std::vector<std::string> minimumItemsToTrade = atomic::split(config.getString("maximum_items_to_trade"), '/');
	int totalOffering = clamp(AuthInventory.item_count(), 1, std::stoi(minimumItemsToTrade[0]));
	int totalRequesting = clamp(VictimInventory.item_count(), 1, std::stoi(minimumItemsToTrade[1]));
	std::vector<std::string> notForTrade;
	bool hasItemsNotForTrade;
	if (config.getString("not_for_trade") == "false") {
		hasItemsNotForTrade = false;
	} else {
		hasItemsNotForTrade = true;
		notForTrade = atomic::split(config.getString("not_for_trade"), ','); // TODO: Pass as parameter
	}
	std::cout << totalOffering << '\n';
	std::cout << totalRequesting << '\n';
	return atomic::Offer{offering, requesting, 0, 0};
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