#ifndef ATOMIC_TRADE_H
#define ATOMIC_TRADE_H
#include "./AuthUser.h"
#include "./Offer.h"
#include "./User.h"

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
		const std::int64_t m_tradeId;
		const atomic::AuthUser m_authUser;
		const atomic::User m_trader;
		const atomic::Offer m_offer;
		const atomic::TradeType m_TradeType;
	public:
		Trade(const std::int64_t& tradeId, const atomic::AuthUser& authUser, const atomic::User& trader, const atomic::Offer& offer, const atomic::TradeType& tradeType) : 
			m_tradeId{ tradeId },
			m_trader{ trader }, m_authUser{ authUser },
			m_offer{ offer }, m_TradeType{ tradeType }
		{
		}

		void decline() const;
		void counter(const atomic::Offer& newOffer) const;
		[[nodiscard]] const atomic::Offer getOffer() const noexcept { return this->m_offer; }
		[[nodiscard]] const atomic::TradeType getTradeType() const noexcept { return this->m_TradeType; }
		[[nodiscard]] const atomic::User getTrader() const noexcept { return this->m_trader; }
	};
}

#endif