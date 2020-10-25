#include <chrono>
#include <future>
#include <thread>
#include <iostream>
#include "../rapidjson/document.h"
#include "../Exceptions.h"
#include "./Demand.h"
#include "./cpr/cpr.h"

size_t getDocumentSize(const rapidjson::Value& val) {
	size_t size = 0;
	for (auto data = val.Begin(); data != val.End(); ++data)
		size++;
	return size;
}

// expensive function btw
std::map<std::int64_t, atomic::Item> atomic::getAllDemand(rolimons::ItemDB& rolimonsItems) {
	std::vector<std::future<atomic::Demand>> futures = {};
	std::vector<atomic::Item> items;
	std::map<std::int64_t, atomic::Item> allItems;
	for (auto item = rolimonsItems["items"].MemberBegin(); item != rolimonsItems["items"].MemberEnd(); ++item) {
		atomic::Item currentItem = rolimons::getItem(rolimonsItems, std::stoll(item->name.GetString()));
		if (currentItem.demand == atomic::Demand::NotAssigned) {
			futures.push_back(std::async(std::launch::async, atomic::getItemDemand, currentItem));
			items.push_back(currentItem);
			std::this_thread::sleep_for(std::chrono::milliseconds(435));
		}
	}
	for (size_t i = 0; i < items.size(); ++i) {
		try {
			items[i].demand = futures[i].get();
			allItems[items[i].id] = items[i];
		}
		catch (atomic::HttpError error){};
	}
	return allItems;
}

atomic::Demand atomic::getItemDemand(const atomic::Item& item) {
	cpr::Url url = {"https://economy.roblox.com/v1/assets/" + std::to_string(item.id) + "/resale-data"};
	std::future<cpr::Response> future = cpr::GetAsync(url);
	cpr::Response r = future.get();
	switch (r.status_code) {
	case 400:
		throw atomic::HttpError{"Invalid AssetId", 400};
	default:
		if (r.status_code != 200)
			throw atomic::HttpError{r.text, r.status_code};
	}
	rapidjson::Document d;
	d.Parse(r.text.c_str());
	size_t salesPointSize = getDocumentSize(d["priceDataPoints"]);
	if (salesPointSize > 175)
		return atomic::Demand::Amazing;
	else if (salesPointSize > 160)
		return atomic::Demand::High;
	else if (salesPointSize > 80)
		return atomic::Demand::Normal;
	else if (salesPointSize < 80 && salesPointSize > 20)
		return atomic::Demand::Low;
	else
		return atomic::Demand::Terrible;
}