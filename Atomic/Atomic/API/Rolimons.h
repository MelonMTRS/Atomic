#ifndef __ATOMIC__ROLIMONS__H
#define __ATOMIC__ROLIMONS__H
#include <cstdint>
#include "../rapidjson/document.h"
#include "../Item.h"

namespace rolimons {
	using ItemDB = rapidjson::Document;

	ItemDB getRolimonItems();
	bool isProjected(ItemDB& items, std::int64_t assetId);
	atomic::RolimonsItem getItem(ItemDB& items, std::int64_t assetId);
	atomic::Item getSpecificItem(ItemDB& items, std::int64_t assetId, std::int64_t userAssetId);
	std::int64_t getItemValue(ItemDB& items, std::int64_t assetId);
}

#endif