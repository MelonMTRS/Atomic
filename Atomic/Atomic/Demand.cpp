#define _SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING
#include <vector>
#include "./Demand.h"
#include "./Exceptions.h"
#include "./Functions.h"
#include "./cpr/cpr.h"
#include "./rapidjson/document.h"

size_t getDocumentSize(const rapidjson::Value& val) {
	size_t size = 0;
	for (auto data = val.Begin(); data != val.End(); ++data)
		size++;
	return size;
}

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
	else if (salesPointSize > 155)
		return atomic::Demand::High;
	else if (salesPointSize > 90)
		return atomic::Demand::Normal;
	else if (salesPointSize > 30)
		return atomic::Demand::Low;
	else
		return atomic::Demand::Terrible;
}

int atomic::getAveragePrice(const atomic::Item& item) {
	std::vector<int> averagePrices;
	const cpr::Url url = { "https://economy.roblox.com/v1/assets/" + std::to_string(item.id) + "/resale-data" };
	cpr::Response r = cpr::Get(url);
	switch (r.status_code) {
	case 400:
		throw atomic::HttpError{ "Invalid AssetId", 400 };
	default:
		if (!atomic::isStatusSuccess(r.status_code))
			throw atomic::HttpError{ r.text, r.status_code };
	}
	rapidjson::Document d;
	d.Parse(r.text.c_str());
	for (auto& v : d["priceDataPoints"].GetArray())
		averagePrices.push_back(v["value"].GetInt());
	return static_cast<int>(computational::getAverage(averagePrices));
}