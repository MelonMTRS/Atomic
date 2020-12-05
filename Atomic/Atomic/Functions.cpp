#include <ctime>
#include <random>
#include "./Functions.h"
#include "./Item.h"

int atomic::random(const int& min, const int& max) {
	std::random_device device;
	std::mt19937 mt(device());
	std::uniform_int_distribution<int> db(min, max);
	return db(mt);
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

std::vector<std::string> atomic::split(const std::string& str, const char& separator) {
	std::vector<std::string> split_items = {};
	std::string stringHolder = "";
	for (size_t i = 0; i < str.size(); ++i) {
		if (str[i] == separator) {
			split_items.push_back(stringHolder);
			stringHolder.clear();
			continue;
		}
		stringHolder += str[i];
	}
	if (!stringHolder.empty())
		split_items.push_back(stringHolder);
	return split_items;
}

bool atomic::isStatusSuccess(const int& status_code) {
	switch (status_code) {
	case 200:
	case 201:
	case 202:
	case 203:
	case 204:
	case 205:
	case 206:
	case 208:
	case 207:
	case 226:
	case 302:
	case 304:
		return true;
	default:
		return false;
	}
}

std::string atomic::lower(const std::string& str) {
	std::string newString = "";
	for (auto c = str.begin(); c != str.end(); ++c) {
		newString += tolower(*c);
	}
	return newString;
}

std::string atomic::upper(const std::string& str) {
	std::string newString = "";
	for (auto c = str.begin(); c != str.end(); ++c) {
		newString += toupper(*c);
	}
	return newString;
}


void atomic::clear() {
	std::system("cls");
}

std::int64_t atomic::getUnixTime() {
	return std::time(nullptr);
}

std::string atomic::secondsToTime(std::int64_t seconds) {
	if (seconds <= 60)
		return std::to_string(seconds) + " seconds";
	else if (seconds <= 3600)
		return std::to_string(seconds / 60) + " minute(s)";
	else if (seconds <= 86400)
		return std::to_string(seconds / 3600) + " hour(s)";
	else
		return std::to_string(seconds / 86400) + " day(s)";
}

// Computational

double computational::getAverage(const std::vector<int>& values) {
	double total = 0;
	size_t totalNumbers = values.size();
	for (auto value = values.begin(); value != values.end(); ++value)
		total += *value;
	return total / totalNumbers;
}

int computational::getPercent(const double& first, const double& second) {
	return static_cast<int>((first / second) * 100);
}