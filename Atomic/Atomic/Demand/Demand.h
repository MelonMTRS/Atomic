#ifndef ATOMIC_DEMAND_DEMAND_H
#define ATOMIC_DEMAND_DEMAND_H
#include "../API/Rolimons.h"
#include "../Item.h"

namespace atomic {
	atomic::Demand getItemDemand(const atomic::Item& item);
}

#endif