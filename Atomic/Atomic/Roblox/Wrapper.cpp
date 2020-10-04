#include <iostream>
#include "../Exceptions.h"
#include "../Conversion.h"
#include "../Trade.h"
#include "./Wrapper.h"
#include "cpr/cpr.h"
// JSON
#include "../rapidjson/document.h"

/*
* cpr's syntax isn't exactly the most beautiful thing in the world
*/

std::string roblox::getToken(const std::string& cookie) {
	cpr::Url logout = { "https://auth.roblox.com/v2/logout" };
	cpr::Cookies authorization = { {".ROBLOSECURITY", atomic::formatCookie(cookie)} };
	cpr::Body empty{""};
	cpr::Response r = cpr::Post(logout, authorization, empty); // Request should fail and return an X-CSRF token along with it
	if (r.status_code != 403)
		throw exceptions::HttpError{"Http Error", r.status_code};
	else
		return r.header["X-CSRF-TOKEN"];
}

atomic::AuthUser roblox::getUserFromCookie(std::string cookie) {
	cookie = atomic::formatCookie(cookie);
	std::string name;
	int id;
	cpr::Response idRequest = cpr::Get(cpr::Url{ "https://www.roblox.com/game/GetCurrentUser.ashx" },
		cpr::Cookies{ {".ROBLOSECURITY", cookie} });
	if (idRequest.status_code != 200)
		throw exceptions::HttpError{"Cookie Authorization Failed", idRequest.status_code, exceptions::ErrorTypes::AuthorizationError};
	id = std::stoi(idRequest.text);
	cpr::Response nameRequest = cpr::Get(cpr::Url{"https://api.roblox.com/users/" + std::to_string(id)});
	if (nameRequest.status_code != 200)
		throw exceptions::HttpError{"User does not exist", nameRequest.status_code};
	rapidjson::Document doc;
	doc.Parse(nameRequest.text.c_str());
	name = doc["Username"].GetString();
	return atomic::AuthUser{name, cookie, id};
}

atomic::Inventory roblox::getInventory(atomic::User user) {
	cpr::Url url = {"https://inventory.roblox.com/v1/users/" + std::to_string(user.getId()) + "/assets/collectibles?limit=100"};
	cpr::Response r = cpr::Get(url);
	switch (r.status_code) {
	case 403:
		throw exceptions::HttpError{ "Permission Failure", 403, exceptions::ErrorTypes::PermissionError };
	case 400:
		throw exceptions::HttpError{ "UserDoesNotExist", 400 };
	}
	if (r.status_code != 200)
		throw exceptions::HttpError{"Inventory fetch failure", r.status_code};
	rapidjson::Document inventory;
	inventory.Parse(r.text.c_str());
	atomic::ItemContainer container;
	for (auto& v : inventory["data"].GetArray()) {
		container.push_back(atomic::Item{
			v["name"].GetString(),
			v["assetId"].GetInt(),
			v["userAssetId"].GetInt64(),
			v["recentAveragePrice"].GetInt()
		});
	}
	return atomic::Inventory{container};
}

bool roblox::can_trade(atomic::AuthUser user, atomic::User target) {
	cpr::Url url = {"https://trades.roblox.com/v1/users/" + std::to_string(target.getId()) + "/can-trade-with"};
	cpr::Cookies cookies = { {".ROBLOSECURITY", user.getCookie()} };
	cpr::Response r = cpr::Get(url, cookies);
	switch (r.status_code) {
	case 403:
		throw exceptions::HttpError{"Permission Error", 403, exceptions::ErrorTypes::PermissionError};
	case 400:
		throw exceptions::HttpError{ "InvalidUser", 400 };
	}
	rapidjson::Document d;
	d.Parse(r.text.c_str());
	return d["canTrade"].GetBool();
}

atomic::Trade roblox::get_trade(atomic::AuthUser user, int tradeId) {
	// Http
	cpr::Url url = {"https://trades.roblox.com/v1/trades/" + std::to_string(tradeId)};
	cpr::Cookies cookies = { {".ROBLOSECURITY", user.getCookie()} };
	cpr::Response r = cpr::Get(url, cookies);
	// Data
	atomic::TradeType tradeType;
	std::vector<atomic::Item> offering = {};
	std::vector<atomic::Item> requesting = {};
	int robuxOffering;
	int robuxRequesting;
	// Exception handling
	switch (r.status_code) {
	case 400:
		throw exceptions::HttpError{ "Not found or not authorized", 400, exceptions::ErrorTypes::NotFoundError };
	case 401:
		throw exceptions::HttpError{ "Permission denied", 401, exceptions::ErrorTypes::AuthorizationError };
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
		offering.push_back(atomic::Item{
			v["name"].GetString(),
			v["assetId"].GetInt(),
			v["id"].GetInt64(),
			v["recentAveragePrice"].GetInt()
		});
	}
	for (auto& v : d["offers"][1]["userAssets"].GetArray()) {
		requesting.push_back(atomic::Item{
			v["name"].GetString(),
			v["assetId"].GetInt(),
			v["id"].GetInt64(),
			v["recentAveragePrice"].GetInt()
		});
	}
	robuxOffering = d["offers"][0]["robux"].GetInt(); // lets be real, no ones gonna offer you more than 2147483647 robux
	robuxRequesting = d["offers"][1]["robux"].GetInt();
	atomic::Offer offer = {offering, requesting, robuxOffering, robuxRequesting};
	atomic::User trader = { d["offers"][1]["user"]["id"].GetInt() };
	return atomic::Trade{ tradeId, trader, offer, tradeType };
}