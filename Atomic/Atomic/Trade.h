#ifndef __ATOMIC__TRADE__H
#define __ATOMIC__TRADE__H
#include "./User.h"
#include "./Offer.h"

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

		The AuthUser is not included here
		*/
	private:
		const int m_tradeId;
		const atomic::User m_trader;
		const atomic::Offer m_offer;
		const atomic::TradeType m_TradeType;
	public:
		Trade(int tradeId, atomic::User trader, atomic::Offer offer, atomic::TradeType tradeType) : 
			m_tradeId{ tradeId }, m_trader{ trader },
			m_offer{ offer }, m_TradeType{ tradeType }
		{
		}

		// Cancels the trade
		// Trade must be either Inbound or Outbound
		const void cancel();

		// Counters the trade
		// Trade must be Inbound
		const void counter(atomic::Offer newOffer);

		// Returns the offer
		[[nodiscard]] const atomic::Offer getOffer() noexcept { return this->m_offer; }

		// Returns the TradeType of the trade
		[[nodiscard]] const atomic::TradeType getTradeType() const noexcept { return this->m_TradeType; }

		// Returns the trader
		[[nodiscard]] const atomic::User getTrader() const noexcept { return this->m_trader; }
	};
}

#endif