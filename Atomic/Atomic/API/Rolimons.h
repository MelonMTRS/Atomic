#ifndef ATOMIC_API_ROLIMONS_H
#define ATOMIC_API_ROLIMONS_H
#include <cstdint>
#include "../rapidjson/document.h"
#include "../Item.h"

namespace rolimons {
	// TODO: Change ItemDB to a class with proper methods for updating values
	using ItemDB = rapidjson::Document;

	struct RolimonsUser {
		int id;
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
}

#endif