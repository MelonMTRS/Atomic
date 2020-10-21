#include "./Bot.h"
#include "./Exceptions.h"

atomic::TradeAction atomic::evaluateTrade(atomic::Trade& trade) {
	if (trade.getTradeType() == atomic::TradeType::Inbound) {
		// TODO: Evaluation here
	}
	return atomic::TradeAction::Ignore; // Temporarily to avoid errors
}

atomic::User atomic::findUser(atomic::AuthUser user, rolimons::ItemDB& items) {
	return atomic::User{0};
}