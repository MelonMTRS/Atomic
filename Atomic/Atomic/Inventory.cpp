#include "./Exceptions.h"
#include "./Functions.h"
#include "./Inventory.h"

[[nodiscard]] const atomic::UniqueItem atomic::Inventory::getRandomItem() const {
	return this->m_inventory[atomic::random(0, this->item_count()-1)];
}

[[nodiscard]] atomic::UniqueItem& atomic::Inventory::findItemByName(const std::string& name) {
	for (auto item = this->begin(); item != this->end(); ++item) {
		if (atomic::lower(name) == atomic::lower(item->name))
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