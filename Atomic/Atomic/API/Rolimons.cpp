#include "cpr/cpr.h"
#include "./Rolimons.h"
#include "../Functions.h"
#include "../Exceptions.h"
#include "../Inventory.h"
#include "../rapidjson/document.h"

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
	const cpr::Url url = "https://www.rolimons.com/itemapi/itemdetails";
	const cpr::Response r = cpr::Get(url);
	if (!atomic::isStatusSuccess(r.status_code))
		throw atomic::HttpError{"RolimonsFetchError", r.status_code};
	rolimons::ItemDB d;
	d.Parse(r.text.c_str());
	return d;
}

[[nodiscard]] rolimons::RolimonsUser rolimons::getUser(ItemDB& items, const int& userId) {
	const cpr::Url url = "https://www.rolimons.com/api/playerassets/" + std::to_string(userId);
	const cpr::Response r = cpr::Get(url);
	switch (r.status_code) {
	case 422:
		throw atomic::HttpError{ "PlayerNotFound", 422, atomic::ErrorTypes::NotFoundError };
	default:
		if (!atomic::isStatusSuccess(r.status_code))
			throw atomic::HttpError{ "PlayerFetchError", r.status_code };
	}
	rapidjson::Document d;
	d.Parse(r.text.c_str());
	atomic::ItemContainer inventory;
	int totalValue = 0;
	int totalRap = 0;
	int totalCollectibles = 0;
	if (d["success"].GetBool()) {
		for (auto asset = d["playerAssets"].MemberBegin(); asset != d["playerAssets"].MemberEnd(); ++asset) {
			if (asset->value.IsArray()) {
				for (auto& v : asset->value.GetArray()) {
					if (v.IsInt64()) {
						atomic::UniqueItem item = rolimons::getSpecificItem(items, std::stoull(asset->name.GetString()), v.GetInt64());
						inventory.push_back(item);
						totalValue += item.value;
						totalRap += item.rap;
					}
					totalCollectibles++;
				}
			}
		}
	}
	return rolimons::RolimonsUser{ userId, atomic::Inventory{ inventory }, totalRap, totalValue, totalCollectibles };
}

[[nodiscard]] bool rolimons::isProjected(rolimons::ItemDB& items, const std::int64_t& assetId) {
	const std::string asset = std::to_string(assetId);
	if (items["items"][asset.c_str()].IsArray()) {
		return items["items"][asset.c_str()][7].GetInt() == 1;
	}
	else {
		throw atomic::ItemNotFound{ "Item could not be found" };
	}
}

[[nodiscard]] atomic::Item rolimons::getItem(rolimons::ItemDB& items, const std::int64_t& assetId) {
	const char* StringAssetId = _strdup(std::to_string(assetId).c_str());
	if (items["items"][StringAssetId].IsArray()) {
		//rapidjson::Value value = items["items"][stringassetId.c_str()].GetArray();
		if (items["items"][StringAssetId][0].IsString() && items["items"][StringAssetId][2].IsInt64() && items["items"][StringAssetId][3].IsInt64()) {
			std::int64_t itemValue = items["items"][StringAssetId][3].GetInt64();
			if (itemValue == -1)
				itemValue = items["items"][StringAssetId][2].GetInt64();
			return atomic::Item{
				items["items"][StringAssetId][0].GetString(),
				assetId,
				items["items"][StringAssetId][2].GetInt64(),
				itemValue,
				getItemDemand(items["items"][StringAssetId][5].GetInt())
			};
		}
		else
			throw atomic::ItemFetchFailure{ "Value mismatch" };
	}
	else
		throw atomic::ItemNotFound{ "Item could not be found" };
}

[[nodiscard]] atomic::Item rolimons::getRandomItem(rolimons::ItemDB& items) {
	const int itemsSize = items["item_count"].GetInt();
	const int randomItem = atomic::random(0, itemsSize-1);
	size_t cursor = 0;
	for (auto item = items["items"].MemberBegin(); item != items["items"].MemberEnd(); ++item) {
		if (cursor != randomItem) {
			cursor++;
		}
		else {
			if (item->value.IsArray()) {
				std::int64_t itemValue = item->value[3].GetInt64();
				if (itemValue == -1)
					itemValue = item->value[2].GetInt64();
				return atomic::Item{
					item->value[0].GetString(),
					std::stoll(item->name.GetString()),
					item->value[2].GetInt64(),
					itemValue,
					getItemDemand(item->value[5].GetInt())
				};
			}
		}
	}
	return rolimons::getRandomItem(items);
}

[[nodiscard]] atomic::UniqueItem rolimons::getSpecificItem(rolimons::ItemDB& items, const std::int64_t& assetId, const std::int64_t& userAssetId) {
	const atomic::Item item = rolimons::getItem(items, assetId);
	return atomic::UniqueItem{item.name, item.id, userAssetId, item.rap, item.value, item.demand};
}

// rolimons::getSpecificItem && rolimons::getItem is recommended instead
[[nodiscard]] std::int64_t rolimons::getItemValue(rolimons::ItemDB& items, const std::int64_t& assetId) {
	const std::string asset = std::to_string(assetId);
	if (items["items"][asset.c_str()].IsArray())
		return items["items"][asset.c_str()].GetArray()[3].GetInt64();
	else
		throw atomic::ItemNotFound{ "Item could not be found" };
}

void rolimons::setItemDemand(ItemDB& items, const std::int64_t& assetId, const atomic::Demand& newDemand) {
	items["items"][std::to_string(assetId).c_str()][5].SetInt(atomic::getDemandId(newDemand));
	/*
	just a reminder for me:
	this should only be used on items with a non assigned demand, to prevent having to get the items demand each time
	we cache it instead
	*/
}