#include "./User.h"
#include "./API/Wrapper.h"

[[nodiscard]] atomic::Inventory atomic::User::getInventory() {
	return roblox::getInventory(*this);
}