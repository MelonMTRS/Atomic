#include "./Bot.h"
#include "./Exceptions.h"

atomic::TradeAction atomic::evaluateTrade(atomic::Trade& trade) {
	if (trade.getTradeType() == atomic::TradeType::Inbound) {
		// TODO: Evaluation here
	}
	return atomic::TradeAction::Ignore; // Temporarily
}