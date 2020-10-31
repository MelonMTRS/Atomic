#ifndef ATOMIC_OFFER_H
#define ATOMIC_OFFER_H
#include <array>
#include <numeric>
#include "./Item.h"

namespace atomic {
	using OfferHolder = std::array<atomic::UniqueItem, 4U>;

	class Offer {
	private:
		OfferHolder m_offering;
		OfferHolder m_requesting;
		int m_robuxOffering = 0;
		int m_robuxRequesting = 0;
	public:
		Offer() = default;
		Offer(const OfferHolder& offering, const OfferHolder& requesting, const int& robuxOffering = 0, const int& robuxRequesting = 0): 
			m_offering{ offering }, m_requesting{ requesting },
			m_robuxOffering{ robuxOffering }, m_robuxRequesting{robuxRequesting}
		{
		}

		[[nodiscard]] inline const OfferHolder& getOffering() const noexcept { return this->m_offering; }
		[[nodiscard]] inline const OfferHolder& getRequesting() const noexcept { return this->m_requesting; }

		[[nodiscard]] inline const int& getRobuxOffered() const noexcept { return this->m_robuxOffering; }
		[[nodiscard]] inline const int& getRobuxRequested() const noexcept { return this->m_robuxRequesting; }

		[[nodiscard]] inline const std::int64_t getTotalOfferedRap() const {
			std::int64_t sum = 0;
			for (auto offer = this->m_offering.begin(); offer != this->m_offering.end(); ++offer) {
				sum += offer->rap;
			}
			return sum;
		}
		[[nodiscard]] inline const std::int64_t getTotalRequestedRap() const {
			std::int64_t sum = 0;
			for (auto request = this->m_requesting.begin(); request != this->m_requesting.end(); ++request) {
				sum += request->rap;
			}
			return sum;
		}
		[[nodiscard]] inline const std::int64_t getTotalOfferedValue() const {
			std::int64_t sum = 0;
			for (auto offer = this->m_offering.begin(); offer != this->m_offering.end(); ++offer) {
				sum += offer->value;
			}
			return sum;
		}
		[[nodiscard]] inline const std::int64_t getTotalRequestedValue() const {
			std::int64_t sum = 0;
			for (auto request = this->m_requesting.begin(); request != this->m_requesting.end(); ++request) {
				sum += request->value;
			}
			return sum;
		}
	};
}

#endif