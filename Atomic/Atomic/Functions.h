#ifndef ATOMIC_FUNCTIONS_H
#define ATOMIC_FUNCTIONS_H
#include <vector>
#include "./Item.h"

// Useful functions

namespace atomic {
	int random(const int& min, const int& max);
	std::string getDemandString(const atomic::Demand& demand);
	int getDemandId(const atomic::Demand& demand);
	std::vector<std::string> split(const std::string& str, const char& separator);
	bool isStatusSuccess(const int& status_code);
	std::string lower(const std::string& str);
	std::string upper(const std::string& str);
	void clear();
	std::int64_t getUnixTime();
	std::string secondsToTime(std::int64_t seconds);

	template<typename Type>
	Type random_choice(const std::vector<Type>& v) {
		return v[atomic::random(0, v.size() - 1)];
	}
}

namespace computational {
	double getAverage(const std::vector<int>& values);
	int getPercent(const double& first, const double& second);
	template<typename Num, typename Lowest, typename Highest>
	[[nodiscard]] constexpr Highest clamp(Num num, Lowest lowest, Highest highest) {
		if (num < lowest)
			return lowest;
		else if (num > highest)
			return highest;
		else
			return num;
	}
}

#endif