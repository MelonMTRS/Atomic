#include <chrono>
#include <future>
#include <thread>
#include <iostream>
#include "../rapidjson/document.h"
#include "../Functions.h"
#include "../Exceptions.h"
#include "./Demand.h"
#include "./cpr/cpr.h"

size_t getDocumentSize(const rapidjson::Value& val) {
	size_t size = 0;
	for (auto data = val.Begin(); data != val.End(); ++data)
		size++;
	return size;
}

// This is NOT an efficient demand calculator, however it's good enough to identify bad items
atomic::Demand atomic::getItemDemand(const atomic::Item& item) {
	const cpr::Url url = {"https://economy.roblox.com/v1/assets/" + std::to_string(item.id) + "/resale-data"};
	cpr::Response r = cpr::Get(url);
	switch (r.status_code) {
	case 400:
		throw atomic::HttpError{"Invalid AssetId", 400};
	default:
		if (!atomic::isStatusSuccess(r.status_code))
			throw atomic::HttpError{r.text, r.status_code};
	}
	rapidjson::Document d;
	d.Parse(r.text.c_str());
	const size_t salesPointSize = getDocumentSize(d["priceDataPoints"]);
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