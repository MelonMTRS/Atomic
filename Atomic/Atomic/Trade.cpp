#include "./Trade.h"

const void atomic::Trade::cancel() {
	if (this->m_TradeType == atomic::TradeType::Inbound || this->m_TradeType == atomic::TradeType::Outbound) {
		// TODO: Canceling here
	}
}

const void atomic::Trade::counter(atomic::Offer newOffer) {
	if (this->m_TradeType == atomic::TradeType::Inbound) {
		// TODO: Countering here
	}
}