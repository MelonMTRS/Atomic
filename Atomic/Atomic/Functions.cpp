#include <random>
#include "./Functions.h"
#include "./Item.h"

int atomic::random(int min, int max) {
	std::random_device device;
	std::mt19937 mt(device());
	std::uniform_int_distribution<int> db(min, max);
	return db(mt);
}

std::string atomic::getItemStringDemand(atomic::Demand demand) {
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
	}
}