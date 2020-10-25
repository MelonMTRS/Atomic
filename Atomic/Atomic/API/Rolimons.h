#ifndef __ATOMIC__ROLIMONS__H
#define __ATOMIC__ROLIMONS__H
#include <cstdint>
#include "../rapidjson/document.h"
#include "../Item.h"

namespace rolimons {
	using ItemDB = rapidjson::Document;

	[[nodiscard]] ItemDB getRolimonItems();
	[[nodiscard]] bool isProjected(ItemDB& items, const std::int64_t& assetId);
	[[nodiscard]] atomic::Item getItem(ItemDB& items, const std::int64_t& assetId);
	[[nodiscard]] atomic::Item getRandomItem(ItemDB& items);
	[[nodiscard]] atomic::UniqueItem getSpecificItem(ItemDB& items, const std::int64_t& assetId, const std::int64_t& userAssetId);
	[[nodiscard]] std::int64_t getItemValue(ItemDB& items, const std::int64_t& assetId);
}

#endif