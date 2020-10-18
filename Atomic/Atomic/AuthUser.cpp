#include "./AuthUser.h"
#include "./API/Wrapper.h"
#include "./API/Rolimons.h"

[[nodiscard]] atomic::Inventory atomic::AuthUser::getInventory(rolimons::ItemDB& items) {
	return roblox::getInventory(atomic::User{ this->m_id }, items);
}