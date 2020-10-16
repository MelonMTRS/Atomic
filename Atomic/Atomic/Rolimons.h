#ifndef __ATOMIC__ROLIMONS__H
#define __ATOMIC__ROLIMONS__H
#include <cstdint>
#include "./rapidjson/document.h"
#include "./Item.h"

namespace rolimons {
	using ItemDB = rapidjson::Document;

	ItemDB& getRolimonsItems();
	bool isProjected(const ItemDB& items, std::int64_t assetId);
	atomic::Item getItem(const ItemDB& items, std::int64_t assetId);
	std::int64_t getItemValue(const ItemDB& items, std::int64_t assetId);
}

#endif