#include "./User.h"
#include "./Offer.h"
#ifndef __ATOMIC__TRADE__H
#define __ATOMIC__TRADE__H

namespace atomic {
	enum class TradeType {
		Inbound,
		Outbound,
		Completed,
		Inactive,
		Unknown
	};

	class Trade {
		/*
		Represents a trade object  
		*/
	private:
		int m_tradeId;
		atomic::User m_trader;
		atomic::Offer m_offer;
		atomic::TradeType m_TradeType;
	public:
		Trade(int tradeId, atomic::User trader, atomic::Offer offer, atomic::TradeType tradeType) : 
			m_tradeId{ tradeId }, m_trader{ trader },
			m_offer{ offer }, m_TradeType{ tradeType }
		{
			
		}

		// Cancels the trade
		// Trade must be either Inbound or Outbound
		void cancel();

		// Counters the trade
		// Trade must be Inbound
		void counter(atomic::Offer newOffer);

		// Returns the offer
		atomic::Offer& getOffer() noexcept { return this->m_offer; }

		// Returns the TradeType of the trade
		atomic::TradeType& getTradeType() noexcept { return this->m_TradeType; }

		atomic::User& getTrader() noexcept { return this->m_trader; }
	};
}

#endif