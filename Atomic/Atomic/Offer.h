#ifndef __ATOMIC__OFFER__H
#define __ATOMIC__OFFER__H
#include <vector>
#include <numeric>
#include "Item.h"

namespace atomic {
	using OfferHolder = std::vector<atomic::Item>;

	class Offer {
	private:
		const OfferHolder m_offering;
		const OfferHolder m_requesting;
		const int m_robuxOffering;
		const int m_robuxRequesting;
	public:
		Offer(OfferHolder offering, OfferHolder requesting, int robuxOffering = 0, int robuxRequesting = 0): 
			m_offering{ offering }, m_requesting{ requesting },
			m_robuxOffering{ robuxOffering }, m_robuxRequesting{robuxRequesting}
		{
		}

		[[nodiscard]] inline const OfferHolder& getOffering() const noexcept { return this->m_offering; }
		[[nodiscard]] inline const OfferHolder& getRequesting() const noexcept { return this->m_requesting; }

		[[nodiscard]] inline const int& getRobuxOffered() const noexcept { return this->m_robuxOffering; }
		[[nodiscard]] inline const int& getRobuxRequested() const noexcept { return this->m_robuxRequesting; }

		[[nodiscard]] inline const int getTotalOfferedRap() const {
			return std::accumulate(this->m_offering.begin(), this->m_offering.end(), 0, [](int accumulator, const atomic::Item& item) {
				return accumulator + item.rap;
			});
		}
		[[nodiscard]] inline const int getTotalRequestedRap() const {
			return std::accumulate(this->m_requesting.begin(), this->m_requesting.end(), 0, [](int accumulator, const atomic::Item& item) {
				return accumulator + item.rap;
			});
		}
		[[nodiscard]] inline const int getTotalOfferedValue() const {
			return std::accumulate(this->m_offering.begin(), this->m_offering.end(), 0, [](int accumulator, const atomic::Item& item) {
				return accumulator + item.value;
			});
		}
		[[nodiscard]] inline const int getTotalRequestedValue() const {
			return std::accumulate(this->m_requesting.begin(), this->m_requesting.end(), 0, [](int accumulator, const atomic::Item& item) {
				return accumulator + item.value;
			});
		}
	};
}

#endif