#include "../Conversion.h"
#include "./Wrapper.h"
#include "cpr/cpr.h"
// JSON
#include "../rapidjson/document.h"

/*
* cpr's syntax isn't exactly the most beautiful thing in the world
*/

atomic::AuthUser roblox::getUserFromCookie(std::string cookie) {
	cookie = atomic::formatCookie(cookie);
	std::string name;
	int id;
	cpr::Response idRequest = cpr::Get(cpr::Url{ "https://www.roblox.com/game/GetCurrentUser.ashx" },
		cpr::Cookies{ {".ROBLOSECURITY", cookie} });
	if (idRequest.status_code != 200)
		throw idRequest.status_code;
	id = std::stoi(idRequest.text);
	cpr::Response nameRequest = cpr::Get(cpr::Url{"https://api.roblox.com/users/" + std::to_string(id)});
	if (nameRequest.status_code != 200)
		throw nameRequest.status_code;
	rapidjson::Document doc;
	doc.Parse(nameRequest.text.c_str());
	name = doc["Username"].GetString();
	return atomic::AuthUser{name, cookie, id};
}