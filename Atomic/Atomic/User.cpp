#include "./User.h"
#include "./API/Wrapper.h"
#include "./API/Rolimons.h"

[[nodiscard]] atomic::Inventory atomic::User::getInventory(rolimons::ItemDB& items) const noexcept {
	return roblox::getInventory(*this, items);
}