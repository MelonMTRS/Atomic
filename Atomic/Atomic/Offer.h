#include <vector>
#include "Item.h"
#ifndef __ATOMIC__OFFER__H
#define __ATOMIC__OFFER__H

/*
	`Offer` is an object that represents a roblox trade,
	can represent TradeType::Inbound, TradeType::Outbound, TradeType::Completed, TradeType::Inactive
*/

namespace atomic {
	using OfferHolder = std::vector<atomic::Item>;

	class Offer {
	private:
		OfferHolder m_offering; // Items the authenticated user is offering
		OfferHolder m_requesting; // Items the authenticated user is requesting
		const int m_robuxOffering;
		const int m_robuxRequesting;
	public:
		Offer(OfferHolder offering, OfferHolder requesting, int robuxOffering = 0, int robuxRequesting = 0): 
			m_offering{ offering }, m_requesting{ requesting },
			m_robuxOffering{ robuxOffering }, m_robuxRequesting{robuxRequesting}
		{
		}

		[[nodiscard]] inline OfferHolder getOffering() const noexcept { return this->m_offering; }
		[[nodiscard]] inline OfferHolder getRequesting() const noexcept { return this->m_requesting; }

		[[nodiscard]] inline const int& getRobuxOffered() const noexcept { return this->m_robuxOffering; }
		[[nodiscard]] inline const int& getRobuxRequested() const noexcept { return this->m_robuxRequesting; }
	};
}

#endif