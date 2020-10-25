#include "./Inventory.h"
#include "./Exceptions.h"
#include "./Functions.h"

[[nodiscard]] atomic::UniqueItem& atomic::Inventory::getRandomItem() {
	return this->m_inventory[atomic::random(0, this->item_count()-1)];
}

[[nodiscard]] atomic::UniqueItem& atomic::Inventory::findItemByName(const std::string& name) {
	auto lower = [&](const std::string& stringToLower) {
		std::string newString = "";
		for (auto c = stringToLower.begin(); c != stringToLower.end(); ++c) {
			newString += tolower(*c);
		}
		return newString;
	};
	for (auto item = this->begin(); item != this->end(); ++item) {
		if (lower(name) == lower(item->name))
			return *item;
	}
	throw atomic::ItemNotFound{"The item " + name + " could not be found"};
}

[[nodiscard]] atomic::UniqueItem& atomic::Inventory::findItemById(const int& assetId) {
	for (auto item = this->begin(); item != this->end(); ++item) {
		if (item->id == assetId)
			return *item;
	}
	throw atomic::ItemNotFound{ "The item " + std::to_string(assetId) + " could not be found" };
}

[[nodiscard]] atomic::ItemContainer atomic::Inventory::itemMatch(const std::function<bool(const atomic::UniqueItem&)>& function) {
	atomic::ItemContainer itemsFound;
	for (auto item = this->begin(); item != this->end(); ++item) {
		if (function(*item))
			itemsFound.push_back(*item);
	}
	return itemsFound;
}