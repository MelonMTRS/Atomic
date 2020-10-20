#include <iostream> // for test
#include "cpr/cpr.h"
#include "./Rolimons.h"
#include "../rapidjson/document.h"
#include "../Exceptions.h"

atomic::Demand getItemDemand(int level) {
	switch (level) {
	case -1:
		return atomic::Demand::NotAssigned;
	case 0:
		return atomic::Demand::Terrible;
	case 1:
		return atomic::Demand::Low;
	case 2:
		return atomic::Demand::Normal;
	case 3:
		return atomic::Demand::High;
	case 4:
		return atomic::Demand::Amazing;
	default:
		return atomic::Demand::Unknown;
	}
}

[[nodiscard]] rolimons::ItemDB rolimons::getRolimonItems() {
	cpr::Url url = {"https://www.rolimons.com/itemapi/itemdetails"};
	cpr::Response r = cpr::Get(url);
	if (r.status_code != 200)
		throw atomic::HttpError{"RolimonsFetchError", r.status_code};
	rolimons::ItemDB d;
	d.Parse(r.text.c_str());
	return d;
}

[[nodiscard]] bool rolimons::isProjected(rolimons::ItemDB& items, std::int64_t assetId) {
	std::string asset = std::to_string(assetId);
	if (items["items"][asset.c_str()].IsArray()) {
		return (items["items"][asset.c_str()][7].GetInt()) == 1;
	}
	else {
		throw atomic::ItemNotFound{ "Item could not be found" };
	}
}

[[nodiscard]] atomic::RolimonsItem rolimons::getItem(rolimons::ItemDB& items, std::int64_t assetId) {
	std::string stringassetId = std::to_string(assetId);
	if (items["items"][stringassetId.c_str()].IsArray()) {
		//rapidjson::Value value = items["items"][stringassetId.c_str()].GetArray();
		if (items["items"][stringassetId.c_str()][0].IsString() && items["items"][stringassetId.c_str()][2].IsInt64() && items["items"][stringassetId.c_str()][3].IsInt64()) {
			int itemValue = items["items"][stringassetId.c_str()][3].GetInt64();
			if (itemValue == -1)
				itemValue = items["items"][stringassetId.c_str()][2].GetInt64();
			return atomic::RolimonsItem{
				items["items"][stringassetId.c_str()][0].GetString(),
				assetId,
				items["items"][stringassetId.c_str()][2].GetInt64(),
				itemValue,
				getItemDemand(items["items"][stringassetId.c_str()][5].GetInt())
			};
		}
		else
			throw atomic::ItemFetchFailure{ "Value mismatch" };
	}
	else
		throw atomic::ItemNotFound{ "Item could not be found" };
}


[[nodiscard]] atomic::Item rolimons::getSpecificItem(rolimons::ItemDB& items, std::int64_t assetId, std::int64_t userAssetId) {
	atomic::RolimonsItem item = rolimons::getItem(items, assetId);
	return atomic::Item{item.name, item.id, userAssetId, item.rap, item.value, item.demand};
}

// rolimons::getSpecificItem && rolimons::getItem is recommended instead
[[nodiscard]] std::int64_t rolimons::getItemValue(rolimons::ItemDB& items, std::int64_t assetId) {
	std::string asset = std::to_string(assetId);
	if (items["items"][asset.c_str()].IsArray())
		return items["items"][asset.c_str()].GetArray()[3].GetInt64();
	else
		throw atomic::ItemNotFound{ "Item could not be found" };
}