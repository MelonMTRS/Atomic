#ifndef ATOMIC_DEMAND_DEMAND_H
#define ATOMIC_DEMAND_DEMAND_H
#include "./API/Rolimons.h"
#include "./Item.h"

namespace atomic {
	atomic::Demand getItemDemand(const atomic::Item& item);
	int getAveragePrice(const atomic::Item& item);
	atomic::Demand getDemandFromId(int level);
	std::string getDemandString(const atomic::Demand& demand);
	int getDemandId(const atomic::Demand& demand);
	atomic::Demand getDemandFromString(const std::string& str);
}

#endif