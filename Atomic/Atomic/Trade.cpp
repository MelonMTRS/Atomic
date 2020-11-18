#include "./API/Wrapper.h"
#include "./Trade.h"

void atomic::Trade::decline() const {
	if (this->m_TradeType == atomic::TradeType::Inbound || this->m_TradeType == atomic::TradeType::Outbound) {
		roblox::declineTrade(this->m_authUser, this->m_tradeId);
	}
}

void atomic::Trade::counter(const atomic::Offer& newOffer) const {
	if (this->m_TradeType == atomic::TradeType::Inbound) {
		// TODO: Countering here
	}
}