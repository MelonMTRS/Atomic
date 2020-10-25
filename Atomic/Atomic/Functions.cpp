#include <random>
#include "./Functions.h"
#include "./Item.h"

int atomic::random(const int& min, const int& max) {
	std::random_device device;
	std::mt19937 mt(device());
	std::uniform_int_distribution<int> db(min, max);
	return db(mt);
}

std::string atomic::getItemStringDemand(const atomic::Demand& demand) {
	switch (demand) {
	case atomic::Demand::NotAssigned:
		return "Not Assigned";
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

std::vector<std::string> atomic::split(const std::string& str, const char& separator) {
	std::vector<std::string> sp = {};
	std::string buffer = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == separator) {
			sp.push_back(buffer);
			buffer = "";
			continue;
		}
		buffer += str[i];
	}
	if (buffer != "")
		sp.push_back(buffer);
	return sp;
}