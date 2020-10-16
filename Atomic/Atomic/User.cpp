#include "./User.h"
#include "./API/Wrapper.h"

[[nodiscard]] atomic::Inventory atomic::User::getInventory() const noexcept {
	return roblox::getInventory(*this);
}