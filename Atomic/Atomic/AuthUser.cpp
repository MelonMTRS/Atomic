#include "./API/Rolimons.h"
#include "./API/Wrapper.h"
#include "./AuthUser.h"
#include "./Exceptions.h"

[[nodiscard]] atomic::Inventory atomic::AuthUser::getInventory(rolimons::ItemDB& items) {
	return rolimons::getUser(items, this->getId()).inventory;
}

[[nodiscard]] const bool atomic::AuthUser::canTradeWith(const atomic::User& user) const {
	return roblox::can_trade(*this, user);
}

[[nodiscard]] const bool atomic::AuthUser::isPremium() const {
	return roblox::getMembership(*this, this->getUser()) == roblox::Membership::Premium;
}