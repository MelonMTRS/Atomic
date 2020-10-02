#include <iostream>
#include "../Exceptions.h"
#include "../Conversion.h"
#include "./Wrapper.h"
#include "cpr/cpr.h"
// JSON
#include "../rapidjson/document.h"

/*
* cpr's syntax isn't exactly the most beautiful thing in the world
*/

std::string roblox::getToken(std::string cookie) {
	cpr::Url logout = { "https://auth.roblox.com/v2/logout" };
	cpr::Cookies authorization = { {".ROBLOSECURITY", atomic::formatCookie(cookie)} };
	cpr::Body empty{""};
	cpr::Response r = cpr::Post(logout, authorization, cpr::Body{""}); // Request should fail and return an X-CSRF token along with it
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
		throw exceptions::HttpError{"Cookie Authorization Failed", idRequest.status_code};
	id = std::stoi(idRequest.text);
	cpr::Response nameRequest = cpr::Get(cpr::Url{"https://api.roblox.com/users/" + std::to_string(id)});
	if (nameRequest.status_code != 200)
		throw exceptions::HttpError{"User does not exist", nameRequest.status_code};
	rapidjson::Document doc;
	doc.Parse(nameRequest.text.c_str());
	name = doc["Username"].GetString();
	return atomic::AuthUser{name, cookie, id};
}