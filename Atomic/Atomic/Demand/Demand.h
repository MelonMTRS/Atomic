#ifndef __ATOMIC__DEMAND__DEMAND__H
#define __ATOMIC__DEMAND__DEMAND__H
#include <vector>
#include "../API/Rolimons.h"
#include "../Item.h"

namespace atomic {
	std::vector<atomic::Item> getAllDemand(rolimons::ItemDB& items); // Asynchronously gets the demand of all items with an unassigned tag
	atomic::Demand getDemand(int assetId);
}

#endif