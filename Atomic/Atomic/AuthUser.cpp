#include "./AuthUser.h"
#include "./API/Wrapper.h"

atomic::Inventory atomic::AuthUser::getInventory() {
	return roblox::getInventory(atomic::User{ this->m_id });
}