#include <algorithm>
#include "./Exceptions.h"
#include "./Functions.h"
#include "./Inventory.h"

[[nodiscard]] const atomic::UniqueItem atomic::Inventory::getRandomItem() const {
	return this->m_inventory[atomic::random(0, this->item_count()-1)];
}

[[nodiscard]] const atomic::UniqueItem atomic::Inventory::getRandomItem(const std::vector<std::string>& notForTrade) const {
	atomic::UniqueItem randomItem = atomic::random_choice(this->m_inventory);
	while (std::find(notForTrade.begin(), notForTrade.end(), std::to_string(randomItem.id)) != std::end(notForTrade)) {
		randomItem = atomic::random_choice(this->m_inventory);
	}
	return randomItem;
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