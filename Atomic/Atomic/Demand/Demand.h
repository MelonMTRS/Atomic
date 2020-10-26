#ifndef __ATOMIC__DEMAND__DEMAND__H
#define __ATOMIC__DEMAND__DEMAND__H
#include <vector>
#include <map>
#include "../API/Rolimons.h"
#include "../Item.h"

namespace atomic {
	atomic::Demand getItemDemand(const atomic::Item& item);
}

#endif