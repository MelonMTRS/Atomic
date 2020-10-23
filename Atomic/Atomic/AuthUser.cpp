#include "./AuthUser.h"
#include "./API/Wrapper.h"
#include "./API/Rolimons.h"

[[nodiscard]] atomic::Inventory atomic::AuthUser::getInventory(rolimons::ItemDB& items) {
	return roblox::getInventory(atomic::User{ this->m_id }, items);
}

[[nodiscard]] const bool atomic::AuthUser::canTradeWith(const atomic::User& user) const {
	return roblox::can_trade(*this, user);
}

[[nodiscard]] const bool atomic::AuthUser::isPremium() const {
	return roblox::getMembership(*this, atomic::User{ this->m_id }) == roblox::Membership::Premium;
}