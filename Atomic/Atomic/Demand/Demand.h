#ifndef __ATOMIC__DEMAND__DEMAND__H
#define __ATOMIC__DEMAND__DEMAND__H
#include <vector>
#include <map>
#include "../API/Rolimons.h"
#include "../Item.h"

namespace atomic {
	std::map<std::int64_t, atomic::Item> getAllDemand(rolimons::ItemDB& items); // Asynchronously gets the demand of all items with an unassigned tag
	atomic::Demand getItemDemand(const atomic::Item& item);
}

#endif