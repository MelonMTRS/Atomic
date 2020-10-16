#ifndef __ATOMIC__OFFER__H
#define __ATOMIC__OFFER__H
#include <vector>
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
	};
}

#endif