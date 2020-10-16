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

		void decline() const;

		void counter(atomic::Offer newOffer) const;

		[[nodiscard]] const atomic::Offer getOffer() const noexcept { return this->m_offer; }

		[[nodiscard]] const atomic::TradeType getTradeType() const noexcept { return this->m_TradeType; }

		[[nodiscard]] const atomic::User getTrader() const noexcept { return this->m_trader; }
	};
}

#endif