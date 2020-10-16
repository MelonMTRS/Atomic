#include <iostream> // for test
#include "cpr/cpr.h"
#include "./Rolimons.h"
#include "../rapidjson/document.h"
#include "../Exceptions.h"

rolimons::ItemDB rolimons::getRolimonItems() {
	cpr::Url url = {"https://www.rolimons.com/itemapi/itemdetails"};
	cpr::Response r = cpr::Get(url);
	if (r.status_code != 200)
		throw atomic::HttpError{"RolimonsFetchError", r.status_code};
	rapidjson::Document d;
	d.Parse(r.text.c_str());
	return d;
}

atomic::RolimonsItem rolimons::getItem(rolimons::ItemDB& items, std::int64_t assetId) {
	std::string stringassetId = std::to_string(assetId);
	if (items["items"][stringassetId.c_str()].IsArray()) {
		rapidjson::Value value = items["items"][stringassetId.c_str()].GetArray();
		if (value[0].IsString() && value[2].IsInt64() && value[3].IsInt64()) {
			return atomic::RolimonsItem{
				value[0].GetString(),
				assetId,
				value[2].GetInt64(),
				value[3].GetInt64()
			};
		}
		else
			throw atomic::ItemFetchFailure{ "Value mismatch" };
	}
	else
		throw atomic::ItemNotFound{ "Item could not be found" };
}


atomic::Item rolimons::getSpecificItem(rolimons::ItemDB& items, std::int64_t assetId, std::int64_t userAssetId) {
	atomic::RolimonsItem item = rolimons::getItem(items, assetId);
	return atomic::Item{item.name, item.id, userAssetId, item.rap, item.value};
}

// rolimons::getSpecificItem && rolimons::getItem is recommended instead
std::int64_t rolimons::getItemValue(rolimons::ItemDB& items, std::int64_t assetId) {
	if (items["items"][std::to_string(assetId).c_str()].IsArray())
		return items["items"][std::to_string(assetId).c_str()].GetArray()[3].GetInt64();
	else
		throw atomic::ItemNotFound{ "Item could not be found" };
}