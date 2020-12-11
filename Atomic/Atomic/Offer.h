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
			return std::reduce(this->m_offering.begin(), this->m_offering.end(), std::int64_t{0}, [](std::int64_t accumulator, atomic::UniqueItem item) -> std::int64_t {
				return accumulator + item.rap;
			});
		}
		[[nodiscard]] inline const std::int64_t getTotalRequestedRap() const {
			return std::reduce(this->m_requesting.begin(), this->m_requesting.end(), std::int64_t{ 0 }, [](std::int64_t accumulator, atomic::UniqueItem item) -> std::int64_t {
				return accumulator + item.rap;
			});
		}
		[[nodiscard]] inline const std::int64_t getTotalOfferedValue() const {
			return std::reduce(this->m_offering.begin(), this->m_offering.end(), std::int64_t{ 0 }, [](std::int64_t accumulator, atomic::UniqueItem item) -> std::int64_t {
				return accumulator + item.value;
			});
		}
		[[nodiscard]] inline const std::int64_t getTotalRequestedValue() const {
			return std::reduce(this->m_requesting.begin(), this->m_requesting.end(), std::int64_t{ 0 }, [](std::int64_t accumulator, atomic::UniqueItem item) -> std::int64_t {
				return accumulator + item.value;
			});
		}
	};
}

#endif