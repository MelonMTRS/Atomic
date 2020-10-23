#include <future> // for std::future
#include "cpr/cpr.h"
#include "./Wrapper.h"
#include "./Rolimons.h"
#include "../Exceptions.h"
#include "../Conversion.h"
#include "../Trade.h"
#include "../Functions.h"
#include "../rapidjson/document.h"

[[nodiscard]] std::string roblox::getToken(const std::string& cookie) {
	cpr::Url logout = { "https://auth.roblox.com/v2/logout" };
	cpr::Cookies authorization = { {".ROBLOSECURITY", atomic::formatCookie(cookie)} };
	cpr::Body empty{""};
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
	if (info.status_code != 200)
		throw atomic::HttpError{"Cookie Authorization Failed", info.status_code, atomic::ErrorTypes::AuthorizationError};
	rapidjson::Document doc;
	doc.Parse(info.text.c_str());
	return atomic::AuthUser{ doc["name"].GetString(), roblox::getToken(cookie), cookie, doc["id"].GetInt() };
}

[[nodiscard]] atomic::Inventory roblox::getInventory(atomic::User user, rolimons::ItemDB& items) {
	cpr::Url url = {"https://inventory.roblox.com/v1/users/" + std::to_string(user.getId()) + "/assets/collectibles?limit=100"}; // TODO: cursoring
	cpr::Response r = cpr::Get(url);
	switch (r.status_code) {
	case 403:
		throw atomic::HttpError{ "Permission Failure", 403, atomic::ErrorTypes::PermissionError };
	case 400:
		throw atomic::HttpError{ "UserDoesNotExist", 400 };
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

[[nodiscard]] bool roblox::can_trade(atomic::AuthUser user, atomic::User target) {
	cpr::Url url = {"https://trades.roblox.com/v1/users/" + std::to_string(target.getId()) + "/can-trade-with"};
	cpr::Cookies cookies = { {".ROBLOSECURITY", user.getCookie()} };
	cpr::Response r = cpr::Get(url, cookies);
	switch (r.status_code) {
	case 403:
		throw atomic::HttpError{"Permission Error", 403, atomic::ErrorTypes::PermissionError};
	case 400:
		throw atomic::HttpError{ "InvalidUser", 400 };
	}
	rapidjson::Document d;
	d.Parse(r.text.c_str());
	return d["canTrade"].GetBool();
}

[[nodiscard]] atomic::Trade roblox::getTrade(atomic::AuthUser& user, rolimons::ItemDB& items, int tradeId) {
	// Http
	cpr::Url url = {"https://trades.roblox.com/v1/trades/" + std::to_string(tradeId)};
	cpr::Cookies cookies = { {".ROBLOSECURITY", user.getCookie()} };
	cpr::Response r = cpr::Get(url, cookies);
	// Data
	atomic::TradeType tradeType;
	std::vector<atomic::UniqueItem> offering = {};
	std::vector<atomic::UniqueItem> requesting = {};
	int robuxOffering;
	int robuxRequesting;
	// Exception handling
	switch (r.status_code) {
	case 400:
		throw atomic::HttpError{ "Not found or not authorized", 400, atomic::ErrorTypes::NotFoundError };
	case 401:
		throw atomic::HttpError{ "Permission denied", 401, atomic::ErrorTypes::AuthorizationError };
	}
	// General
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
	for (auto& v : d["offers"][0]["userAssets"].GetArray()) {
		if (v["name"].IsString() && v["assetId"].IsInt64() && v["userAssetId"].IsInt64() && v["recentAveragePrice"].IsInt64()) {
			offering.push_back(rolimons::getSpecificItem(items, v["assetId"].GetInt64(), v["userAssetId"].GetInt64()));
		}
	}
	for (auto& v : d["offers"][1]["userAssets"].GetArray()) {
		if (v["name"].IsString() && v["assetId"].IsInt64() && v["userAssetId"].IsInt64() && v["recentAveragePrice"].IsInt64()) {
			requesting.push_back(rolimons::getSpecificItem(items, v["assetId"].GetInt64(), v["userAssetId"].GetInt64()));
		}
	}
	robuxOffering = d["offers"][0]["robux"].GetInt(); // lets be real, no ones gonna offer you more than 2147483647 robux
	robuxRequesting = d["offers"][1]["robux"].GetInt();
	atomic::Offer offer = {offering, requesting, robuxOffering, robuxRequesting};
	atomic::User trader = { d["offers"][1]["user"]["id"].GetInt() };
	return atomic::Trade{ tradeId, trader, offer, tradeType };
}

[[nodiscard]] std::vector<atomic::User> roblox::getResellers(atomic::AuthUser user, atomic::Item item) {
	std::vector<atomic::User> users;
	cpr::Url url = {"https://economy.roblox.com/v1/assets/" + std::to_string(item.id) + "/resellers?limit=100"};
	cpr::Cookies cookies = { {".ROBLOSECURITY", user.getCookie()} };
	cpr::Response r = cpr::Get(url, cookies);
	switch (r.status_code) {
	case 401:
		throw atomic::HttpError{"Authorization Denied", 401, atomic::ErrorTypes::AuthorizationError};
	default:
		if (r.status_code != 200)
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

[[nodiscard]] roblox::Membership roblox::getMembership(atomic::AuthUser authuser, atomic::User user) {
	cpr::Url url = { "https://premiumfeatures.roblox.com/v1/users/" + std::to_string(user.getId()) + "/validate-membership" };
	cpr::Cookies cookies = { {".ROBLOSECURITY", authuser.getCookie()} };
	cpr::Response r = cpr::Get(url, cookies);
	if (r.status_code != 200)
		throw atomic::HttpError{"HttpError", r.status_code};
	return r.text == "true" ? roblox::Membership::Premium : roblox::Membership::Normal;
}

[[nodiscard]] std::vector<atomic::User>& roblox::getUsersInGroup(int groupId, std::int64_t roleId) {
	std::string sortOrder = atomic::random(0, 1) ? "Asc" : "Desc"; // TODO: Move to parameter
	std::vector<atomic::User> users;
	cpr::Url url = {"https://groups.roblox.com/v1/groups/" + std::to_string(groupId) + "/roles/" + std::to_string(roleId) + "/users?cursor=&limit=100&sortOrder=" + sortOrder};
	cpr::Response r = cpr::Get(url);
	switch (r.status_code) {
	case 400:
		throw atomic::HttpError{"Group invalid or does not exist", 400, atomic::ErrorTypes::NotFoundError};
	case 403:
		throw atomic::HttpError{"RoleSetId is invalid or does not exist", 403, atomic::ErrorTypes::NotFoundError};
	default:
		if (r.status_code != 200)
			throw atomic::HttpError{r.text, r.status_code};
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