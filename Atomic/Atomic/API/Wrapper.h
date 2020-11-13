#ifndef ATOMIC_API_WRAPPER_H
#define ATOMIC_API_WRAPPER_H
#include <string>
#include "./Rolimons.h"
#include "../User.h"
#include "../Inventory.h"
#include "../Offer.h"
#include "../AuthUser.h"
#include "../Trade.h"

namespace roblox {
	enum class Membership {
		Normal,
		Premium
	};

	[[nodiscard]] std::string getToken(const std::string& cookie);
	[[nodiscard]] atomic::AuthUser getUserFromCookie(std::string cookie);
	[[nodiscard]] roblox::Membership getMembership(const atomic::AuthUser& authuser, const atomic::User& user);
	[[nodiscard]] atomic::Inventory getInventory(const atomic::User& user, rolimons::ItemDB& items);
	std::int64_t sendTrade(const atomic::AuthUser& user, const atomic::Trade& trade);
	void acceptTrade(const atomic::AuthUser& user, const int& tradeId);
	void counterTrade(const atomic::AuthUser& user, const int& tradeId, const atomic::Offer& newOffer);
	void declineTrade(const atomic::AuthUser& user, const int& tradeId);
	[[nodiscard]] bool can_trade(const atomic::AuthUser& user, const atomic::User& target);
	[[nodiscard]] atomic::Trade getTrade(const atomic::AuthUser& user, rolimons::ItemDB& items, const std::int64_t& tradeId);
	[[nodiscard]] std::vector<atomic::User> getResellers(const atomic::AuthUser& user, const atomic::Item& item);
	[[nodiscard]] std::vector<atomic::User> getUsersInGroup(const int& groupId, const std::int64_t& roleId);
	[[nodiscard]] std::vector<std::int64_t> getTrades(const atomic::AuthUser& user, const atomic::TradeType& tradeType, const int& limit=25);
}

#endif