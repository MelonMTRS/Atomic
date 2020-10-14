#include "./Inventory.h"
#include "./Exceptions.h"

atomic::Item& atomic::Inventory::findItemByName(const std::string& name) {
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

atomic::Item& atomic::Inventory::findItemById(int assetId) {
	for (auto item = this->begin(); item != this->end(); ++item) {
		if (item->id == assetId)
			return *item;
	}
	throw atomic::ItemNotFound{ "The item " + std::to_string(assetId) + " could not be found" };
}

atomic::ItemContainer atomic::Inventory::itemMatch(std::function<bool(const atomic::Item&)> function) { // TODO: test by const reference
	atomic::ItemContainer itemsFound;
	for (auto item = this->begin(); item != this->end(); ++item) {
		if (function(*item))
			itemsFound.push_back(*item);
	}
	return itemsFound; // Returns the items found, if no matches, then returns an empty ItemContainer
}