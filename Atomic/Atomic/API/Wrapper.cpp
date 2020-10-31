#include <array>
#include "cpr/cpr.h"
#include "./Wrapper.h"
#include "./Rolimons.h"
#include "../Exceptions.h"
#include "../Conversion.h"
#include "../Trade.h"
#include "../Functions.h"
#include "../rapidjson/document.h"

[[nodiscard]] std::string roblox::getToken(const std::string& cookie) {
	const cpr::Url logout = { "https://auth.roblox.com/v2/logout" };
	const cpr::Cookies authorization = { {".ROBLOSECURITY", atomic::formatCookie(cookie)} };
	const cpr::Body empty{""};
	cpr::Response r = cpr::Post(logout, authorization, empty);
	if (r.status_code != 403)
		throw atomic::HttpError{"Http Error", r.status_code};
	else
		return r.header["X-CSRF-TOKEN"];
}

[[nodiscard]] atomic::AuthUser roblox::getUserFromCookie(std::string cookie) {
	cookie = atomic::formatCookie(cookie);
	cpr::Response info = cpr::Get(cpr::Url{ "https://users.roblox.com/v1/users/authenticated" },
								  cpr::Cookies{ {".ROBLOSECURITY", cookie} });
	if (!atomic::isStatusSuccess(info.status_code))
		throw atomic::HttpError{"Cookie Authorization Failed", info.status_code, atomic::ErrorTypes::AuthorizationError};
	rapidjson::Document doc;
	doc.Parse(info.text.c_str());
	return atomic::AuthUser{ doc["name"].GetString(), roblox::getToken(cookie), cookie, doc["id"].GetInt() };
}

[[nodiscard]] atomic::Inventory roblox::getInventory(const atomic::User& user, rolimons::ItemDB& items) {
	const cpr::Url url = {"https://inventory.roblox.com/v1/users/" + std::to_string(user.getId()) + "/assets/collectibles?limit=100"}; // TODO: cursoring
	cpr::Response r = cpr::Get(url);
	switch (r.status_code) {
	case 403:
		throw atomic::HttpError{ "Permission Failure", 403, atomic::ErrorTypes::PermissionError };
	case 400:
		throw atomic::HttpError{ "UserDoesNotExist", 400 };
	default:
		if (!atomic::isStatusSuccess(r.status_code))
			throw atomic::HttpError{ r.text, r.status_code };
	}
	if (r.status_code != 200)
		throw atomic::HttpError{"Inventory fetch failure", r.status_code};
	rapidjson::Document inventory;
	inventory.Parse(r.text.c_str());
	atomic::ItemContainer container;
	for (auto& v : inventory["data"].GetArray()) {
		if (v["name"].IsString() && v["assetId"].IsInt64() && v["userAssetId"].IsInt64() && v["recentAveragePrice"].IsInt64()) {
			container.push_back(rolimons::getSpecificItem(items, v["assetId"].GetInt64(), v["userAssetId"].GetInt64()));
		}
	}
	return atomic::Inventory{container};
}

[[nodiscard]] bool roblox::can_trade(const atomic::AuthUser& user, const atomic::User& target) {
	const cpr::Url url = {"https://trades.roblox.com/v1/users/" + std::to_string(target.getId()) + "/can-trade-with"};
	const cpr::Cookies cookies = { {".ROBLOSECURITY", user.getCookie()} };
	cpr::Response r = cpr::Get(url, cookies);
	switch (r.status_code) {
	case 403:
		throw atomic::HttpError{"Permission Error", 403, atomic::ErrorTypes::PermissionError};
	case 400:
		throw atomic::HttpError{ "InvalidUser", 400 };
	default:
		if (!atomic::isStatusSuccess(r.status_code))
			throw atomic::HttpError{ r.text, r.status_code };
	}
	rapidjson::Document d;
	d.Parse(r.text.c_str());
	return d["canTrade"].GetBool();
}

[[nodiscard]] atomic::Trade roblox::getTrade(const atomic::AuthUser& user, rolimons::ItemDB& items, const int& tradeId) {
	const cpr::Url url = {"https://trades.roblox.com/v1/trades/" + std::to_string(tradeId)};
	const cpr::Cookies cookies = { {".ROBLOSECURITY", user.getCookie()} };
	cpr::Response r = cpr::Get(url, cookies);
	atomic::TradeType tradeType;
	std::array<atomic::UniqueItem, 4U> offering = {};
	std::array<atomic::UniqueItem, 4U> requesting = {};
	//std::vector<atomic::UniqueItem> offering = {};
	//std::vector<atomic::UniqueItem> requesting = {};
	int robuxOffering;
	int robuxRequesting;
	switch (r.status_code) {
	case 400:
		throw atomic::HttpError{ "Not found or not authorized", 400, atomic::ErrorTypes::NotFoundError };
	case 401:
		throw atomic::HttpError{ "Permission denied", 401, atomic::ErrorTypes::AuthorizationError };
	default:
		if (!atomic::isStatusSuccess(r.status_code))
			throw atomic::HttpError{ r.text, r.status_code };
	}
	rapidjson::Document d;
	d.Parse(r.text.c_str());
	std::string status = d["status"].GetString();
	if (status == "Completed")
		tradeType = atomic::TradeType::Completed;
	else if (status == "Expired")
		tradeType = atomic::TradeType::Inactive;
	else if (status == "Open")
		tradeType = atomic::TradeType::Outbound;
	else if (d["isActive"].GetBool())
		tradeType = atomic::TradeType::Inbound;
	else
		tradeType = atomic::TradeType::Unknown;
	int offeringIterator = 0;
	for (auto& v : d["offers"][0]["userAssets"].GetArray()) {
		if (v["name"].IsString() && v["assetId"].IsInt64() && v["id"].IsInt64() && v["recentAveragePrice"].IsInt64()) {
			offering[offeringIterator] = rolimons::getSpecificItem(items, v["assetId"].GetInt64(), v["id"].GetInt64());
			offeringIterator++;
		}
	}
	int requestingIterator = 0;
	for (auto& v : d["offers"][1]["userAssets"].GetArray()) {
		if (v["name"].IsString() && v["assetId"].IsInt64() && v["id"].IsInt64() && v["recentAveragePrice"].IsInt64()) {
			requesting[requestingIterator] = rolimons::getSpecificItem(items, v["assetId"].GetInt64(), v["id"].GetInt64());
			requestingIterator++;
		}
	}
	robuxOffering = d["offers"][0]["robux"].GetInt(); // lets be real, no ones gonna offer you more than 2147483647 robux
	robuxRequesting = d["offers"][1]["robux"].GetInt();
	atomic::Offer offer = {offering, requesting, robuxOffering, robuxRequesting};
	atomic::User trader = { d["offers"][1]["user"]["id"].GetInt() };
	return atomic::Trade{ tradeId, user, trader, offer, tradeType };
}

[[nodiscard]] std::vector<atomic::User> roblox::getResellers(const atomic::AuthUser& user, const atomic::Item& item) {
	std::vector<atomic::User> users;
	const cpr::Url url = {"https://economy.roblox.com/v1/assets/" + std::to_string(item.id) + "/resellers?limit=100"};
	const cpr::Cookies cookies = { {".ROBLOSECURITY", user.getCookie()} };
	cpr::Response r = cpr::Get(url, cookies);
	switch (r.status_code) {
	case 401:
		throw atomic::HttpError{"Authorization Denied", 401, atomic::ErrorTypes::AuthorizationError};
	default:
		if (!atomic::isStatusSuccess(r.status_code))
			throw atomic::HttpError{ r.text, r.status_code };
	}
	rapidjson::Document d;
	d.Parse(r.text.c_str());
	for (auto user = d["data"].Begin(); user != d["data"].End(); ++user) {
		if ((*user)["seller"]["id"].IsInt64() && (*user)["seller"]["name"].IsString()) {
			users.push_back(atomic::User{
				(*user)["seller"]["id"].GetInt64(),
				(*user)["seller"]["name"].GetString(),
			});
		}
	}
	return users;
}

[[nodiscard]] roblox::Membership roblox::getMembership(const atomic::AuthUser& authuser, const atomic::User& user) {
	const cpr::Url url = { "https://premiumfeatures.roblox.com/v1/users/" + std::to_string(user.getId()) + "/validate-membership" };
	const cpr::Cookies cookies = { {".ROBLOSECURITY", authuser.getCookie()} };
	cpr::Response r = cpr::Get(url, cookies);
	if (!atomic::isStatusSuccess(r.status_code))
		throw atomic::HttpError{"HttpError", r.status_code};
	return r.text == "true" ? roblox::Membership::Premium : roblox::Membership::Normal;
}

[[nodiscard]] std::vector<atomic::User> roblox::getUsersInGroup(const int& groupId, const std::int64_t& roleId) {
	const std::string sortOrder = atomic::random(0, 1) ? "Asc" : "Desc"; // TODO: Move to parameter
	const cpr::Url url = {"https://groups.roblox.com/v1/groups/" + std::to_string(groupId) + "/roles/" + std::to_string(roleId) + "/users?cursor=&limit=100&sortOrder=" + sortOrder};
	std::vector<atomic::User> users;
	cpr::Response r = cpr::Get(url);
	switch (r.status_code) {
	case 400:
		throw atomic::HttpError{"Group invalid or does not exist", 400, atomic::ErrorTypes::NotFoundError};
	case 403:
		throw atomic::HttpError{"RoleSetId is invalid or does not exist", 403, atomic::ErrorTypes::NotFoundError};
	default:
		if (!atomic::isStatusSuccess(r.status_code))
			throw atomic::HttpError{ r.text, r.status_code };
	}
	rapidjson::Document data;
	data.Parse(r.text.c_str());
	for (auto& user : data["data"].GetArray()) {
		if (user["userId"].IsInt64() && user["username"].IsString()) {
			users.push_back(atomic::User{
				user["userId"].GetInt64(),
				user["username"].GetString()
			});
		}
	}
	return users;
}