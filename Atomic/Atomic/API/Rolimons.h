#ifndef ATOMIC_API_ROLIMONS_H
#define ATOMIC_API_ROLIMONS_H
#include "../Inventory.h"
#include "../Item.h"
#include "../rapidjson/document.h"

namespace rolimons {
	using ItemDB = rapidjson::Document;

	struct RolimonsUser {
		int id;
		atomic::Inventory inventory;
		int rap;
		int value;
		int collectiblesCount;
	};

	[[nodiscard]] ItemDB getRolimonItems();
	[[nodiscard]] bool isProjected(ItemDB& items, const std::int64_t& assetId);
	[[nodiscard]] atomic::Item getItem(ItemDB& items, const std::int64_t& assetId);
	[[nodiscard]] atomic::Item getRandomItem(ItemDB& items);
	[[nodiscard]] atomic::UniqueItem getSpecificItem(ItemDB& items, const std::int64_t& assetId, const std::int64_t& userAssetId);
	[[nodiscard]] std::int64_t getItemValue(ItemDB& items, const std::int64_t& assetId);
	[[nodiscard]] RolimonsUser getUser(ItemDB& items, const int& userId);
	void setItemDemand(ItemDB& items, const std::int64_t& assetId, const atomic::Demand& newDemand);
}

#endif