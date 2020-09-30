#include "./Offer.h"
#ifndef __ATOMIC__TRADE__H
#define __ATOMIC__TRADE__H

namespace atomic {
	enum class TradeType {
		Inbound,
		Outbound,
		Completed,
		Inactive
	};

	class Trade {
		/*
		Represents a trade object
		*/
	private:
		int m_tradeId;
		atomic::Offer m_offer;
		atomic::TradeType m_TradeType;
	public:
		Trade(int tradeId, atomic::Offer offer, atomic::TradeType tradeType)
			: m_tradeId{ tradeId }, m_offer{ offer }, m_TradeType{tradeType}
		{
			
		}

		// Cancels the trade
		// Trade must be either Inbound or Outbound
		void cancel();

		// Counters the trade
		// Trade must be Inbound
		void counter(atomic::Offer newOffer);
	};
}

#endif