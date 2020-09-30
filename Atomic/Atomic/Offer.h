#include <array>
#include "Item.h"
#ifndef __ATOMIC__OFFER__H
#define __ATOMIC__OFFER__H

/*
	`Offer` is an object that represents a roblox trade
*/

namespace atomic {
	using OfferHolder = std::array<atomic::Item, 4>;

	class Offer {
	private:
		OfferHolder m_offering; // Items the authenticated user is offering
		OfferHolder m_requesting; // Items the authenticated user is requesting
	public:
		Offer(OfferHolder offering, OfferHolder requesting)
			: m_offering{ offering }, m_requesting{requesting}
		{
		}

		inline OfferHolder getOffering() { return this->m_offering; }
		inline OfferHolder getRequesting() { return this->m_requesting; }
	};
}

#endif