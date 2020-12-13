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
	else if (salesPointSize > 120)
		return atomic::Demand::Normal;
	else if (salesPointSize > 40)
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

atomic::Demand atomic::getDemandFromId(int level) {
	switch (level) {
	case -1:
		return atomic::Demand::NotAssigned;
	case 0:
		return atomic::Demand::Terrible;
	case 1:
		return atomic::Demand::Low;
	case 2:
		return atomic::Demand::Normal;
	case 3:
		return atomic::Demand::High;
	case 4:
		return atomic::Demand::Amazing;
	default:
		return atomic::Demand::Unknown;
	}
}

std::string atomic::getDemandString(const atomic::Demand& demand) {
	switch (demand) {
	case atomic::Demand::NotAssigned:
		return "NotAssigned";
	case atomic::Demand::Terrible:
		return "Terrible";
	case atomic::Demand::Low:
		return "Low";
	case atomic::Demand::Normal:
		return "Normal";
	case atomic::Demand::High:
		return "High";
	case atomic::Demand::Amazing:
		return "Amazing";
	default:
		return "Unknown";
	}
}

atomic::Demand atomic::getDemandFromString(const std::string& str) {
	if (str == "NotAssigned")
		return atomic::Demand::NotAssigned;
	else if (str == "Terrible")
		return atomic::Demand::Terrible;
	else if (str == "Low")
		return atomic::Demand::Low;
	else if (str == "Normal")
		return atomic::Demand::Normal;
	else if (str == "High")
		return atomic::Demand::High;
	else if (str == "Amazing")
		return atomic::Demand::Amazing;
	else
		return atomic::Demand::Unknown;
}

int atomic::getDemandId(const atomic::Demand& demand) {
	switch (demand) {
	case atomic::Demand::NotAssigned:
		return -1;
	case atomic::Demand::Terrible:
		return 0;
	case atomic::Demand::Low:
		return 1;
	case atomic::Demand::Normal:
		return 2;
	case atomic::Demand::High:
		return 3;
	case atomic::Demand::Amazing:
		return 4;
	default:
		return 404;
	}
}