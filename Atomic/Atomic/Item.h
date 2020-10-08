#include <string>
#ifndef __ATOMIC__ITEM__H
#define __ATOMIC__ITEM__H

namespace atomic {
	struct Item {
		const std::string name;
		const __int64 id;
		const __int64 userAssetId; // Unique Identifier Id
		const int rap;
	};
}

#endif