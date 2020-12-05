#include <array>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <tuple>
#include <thread>
#include "./API/Rolimons.h"
#include "./API/Wrapper.h"
#include "./Bot.h"
#include "./Config/Parser.h"
#include "./Demand.h"
#include "./Exceptions.h"
#include "./Functions.h"
#include "./Item.h"
#include "./Offer.h"

/*
	warning: you're about to enter the land of spaghetti
*/

[[nodiscard]] atomic::TradeAction atomic::evaluateTrade(rolimons::ItemDB& items, const atomic::Trade& trade, config::Config& config) {
	std::int64_t totalOffering = trade.getOffer().getTotalOfferedValue();
	std::int64_t totalRequesting = trade.getOffer().getTotalRequestedValue();
	atomic::Offer offer = trade.getOffer();
	if (offer.getTotalRequestedValue() > config.getInt64("ignore_trades_above"))
		return TradeAction::Ignore;
	std::vector<std::string> notForTrade;
	bool hasItemsNotForTrade;
	if (config.getString("not_for_trade") == "false") {
		hasItemsNotForTrade = false;
	}
	else {
		hasItemsNotForTrade = true;
		notForTrade = atomic::split(config.getString("not_for_trade"), ','); // TODO: Pass as parameter
	}
	if (hasItemsNotForTrade) {
		for (auto item = offer.getRequesting().begin(); item != offer.getRequesting().end(); ++item) {
			if (std::find(notForTrade.begin(), notForTrade.end(), std::to_string(item->id)) != notForTrade.end())
				continue;
		}
	}
	if (offer.getRobuxOffered() != 0 || offer.getRobuxRequested() != 0)
		return TradeAction::Ignore;
	if (totalOffering > totalRequesting) {
		for (auto item = offer.getOffering().begin(); item != offer.getOffering().end(); ++item) {
			if (item->id != 0) {
				if (rolimons::isProjected(items, item->id))
					return TradeAction::Decline;
				atomic::Demand itemDemand = item->demand;
				if (itemDemand == atomic::Demand::NotAssigned) {
					itemDemand = atomic::getItemDemand(*item);
					rolimons::setItemDemand(items, item->id, itemDemand);
				}
				if (itemDemand == atomic::Demand::Terrible)
					return TradeAction::Decline;
			}
		}
		for (auto item = offer.getOffering().begin(); item != offer.getOffering().end(); ++item) {
			if (computational::getPercent(atomic::getAveragePrice(*item), static_cast<double>(item->rap)) < 35) {
				// Probably a projected and rolimons hasn't caught on to it yet
				return atomic::TradeAction::Decline;
			}
		}
		return TradeAction::Accept;
	}
	else {
		return TradeAction::Decline;
	}
	return TradeAction::Ignore;
}

bool itemExists(const atomic::OfferHolder& offer, const std::int64_t& userAssetId) {
	for (const auto& item : offer) {
		if (item.userAssetId == userAssetId)
			return true;
	}
	return false;
}

[[nodiscard]] std::tuple<atomic::Offer, int> atomic::makeOffer(const atomic::Inventory& AuthInventory, const atomic::Inventory& VictimInventory, config::Config& config, rolimons::ItemDB& items, int tries) {
	if (AuthInventory.item_count() == 0)
		atomic::throwException("You do not have any limited items, cannot create trades.");
	if (VictimInventory.item_count() < 3)
		throw atomic::TradeFormFailure{atomic::TradeErrorTypes::USER_LACKS_ITEMS};
	std::map<int64_t, atomic::Demand> demandCache = {};
	atomic::OfferHolder offering{};
	atomic::OfferHolder requesting{};
	int offeringCursor = 0;
	int requestingCursor = 0;
	std::vector<std::string> minimumItemsToTrade = atomic::split(config.getString("maximum_items_to_trade"), '/');
	int totalOffering = computational::clamp(AuthInventory.item_count(), 1, std::stoi(minimumItemsToTrade[0]));
	int totalRequesting = computational::clamp(VictimInventory.item_count(), 1, std::stoi(minimumItemsToTrade[1]));
	std::vector<std::string> notForTrade;
	bool hasItemsNotForTrade;
	if (config.getString("not_for_trade") == "false") {
		hasItemsNotForTrade = false;
	} else {
		hasItemsNotForTrade = true;
		notForTrade = atomic::split(config.getString("not_for_trade"), ','); // TODO: Pass as parameter
	}
	int totalProfit = 0;
	bool breakNest = false;
	for (int i = 0; i < totalRequesting && !breakNest; ++i) {
		atomic::UniqueItem randomItem = VictimInventory.getRandomItem();
		for (const auto& item : AuthInventory.items()) {
			if (hasItemsNotForTrade) {
				if (std::find(notForTrade.begin(), notForTrade.end(), std::to_string(item.id)) != notForTrade.end())
					continue;
			}
			if (item.value > config.getInt64("max_item_value") || itemExists(offering, item.userAssetId))
				continue;
			if (rolimons::isProjected(items, randomItem.id))
				continue;
			int itemTries = 0;
			while (itemExists(requesting, randomItem.userAssetId) && itemTries < 25 || randomItem.demand == Demand::Terrible) {
				randomItem = VictimInventory.getRandomItem();
				itemTries++;
			}
			if (randomItem.demand == atomic::Demand::NotAssigned && demandCache.find(randomItem.id) == demandCache.end()) {
				try {
					atomic::Demand itemDemand = atomic::getItemDemand(randomItem);
					std::cout << "Changed demand of " << randomItem.name << " from " << atomic::getDemandString(randomItem.demand) << " to " << atomic::getDemandString(itemDemand) << '\n';
					randomItem.demand = itemDemand;
					rolimons::setItemDemand(items, randomItem.id, itemDemand);
					demandCache[randomItem.id] = itemDemand;
					std::this_thread::sleep_for(std::chrono::milliseconds(500)); // To prevent rate limits
				}
				catch (const atomic::HttpError& error) {};
			}
			if (randomItem.demand == atomic::Demand::NotAssigned && demandCache.find(randomItem.id) != demandCache.end())
				randomItem.demand = demandCache[randomItem.id];
			if (randomItem.demand < item.demand && !(item.demand == Demand::Amazing && (randomItem.demand == Demand::High || randomItem.demand == Demand::Normal))) {
				continue;
			}
			if (offeringCursor >= totalOffering || requestingCursor >= totalRequesting) {
				breakNest = true;
				break;
			}
			if (item.value < randomItem.value) {
				if ((randomItem.value - item.value) > (config.getInt64("minimum_profit")/2) && (randomItem.value - item.value) < (config.getInt64("minimum_profit")*2)) {
					offering[offeringCursor++] = item;
					requesting[requestingCursor++] = randomItem;
					totalProfit += randomItem.value - item.value;
					if (totalProfit >= config.getInt64("minimum_profit"))
						breakNest = true;
				}
				else
					continue;
			}
			else
				continue;
		}
	}
	if (offeringCursor == 0 || requestingCursor == 0) {
		//if (tries < 15) {
		//	return atomic::makeOffer(AuthInventory, VictimInventory, config, items, tries+1);
		//}
		throw atomic::TradeFormFailure{ atomic::TradeErrorTypes::COULD_NOT_CREATE };
	}
	if (totalProfit < config.getInt64("minimum_profit") && requestingCursor < totalRequesting) { // Doesn't meet the minimum profit, look for an item to add.
		int requiredAmount = config.getInt64("minimum_profit") - totalProfit;
		for (const auto& item : VictimInventory.items()) {
			if (hasItemsNotForTrade) {
				if (std::find(notForTrade.begin(), notForTrade.end(), std::to_string(item.id)) != notForTrade.end())
					continue;
			}
			if (item.value >= requiredAmount && item.value < config.getInt64("minimum_profit")*3 && !itemExists(requesting, item.userAssetId)) {
				requesting[requestingCursor++] = item;
				totalProfit += item.value;
				break;
			}
		}
	}
	if (totalProfit > config.getInt64("minimum_profit") * 3 && requestingCursor > 1) { // Profit is too large, remove a requested item
		for (const auto& item : requesting) {
			if (item.value <= config.getInt64("minimum_profit") * 1.5) {
				std::remove(requesting.begin(), requesting.end(), item);
				break;
			}
		}
	}
	return std::make_tuple(atomic::Offer{offering, requesting, 0, 0}, totalProfit);
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