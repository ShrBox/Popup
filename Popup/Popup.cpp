#include "pch.h"

void entry() {
	std::cout << "[Popup] loaded\n";
}

short ticks = 0;

string popup(const ItemStack* item, money_t money, int plevel) {
	string permLevel;
	std::string itemName;
	if (!item->getId() == 0) {
		SymCall("?getSerializedName@Item@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ",
			void, const Item*, std::string*)(item->getItem(), &itemName);
	}
	else {
		itemName = u8"����";
	}
	
	switch (plevel) {
	case 1:
		permLevel = u8"��c��l����Ա";
		break;
	case 0:
		permLevel = u8"��a��l���";
		break;
	default:
		permLevel = std::to_string(plevel);
	}
	return u8"\n��r��bȨ�޵ȼ�: " + permLevel + u8"  ��r��b��Ǯ: ��e��l" + std::to_string(money) +
		u8"\n��r��b��Ʒ: ��a��l" + itemName + ":" + std::to_string(item->getId());
}

THook(void, "?normalTick@Player@@UEAAXXZ", Player* player) {
	ticks++;
	if (ticks == 20) {
		WPlayer wp = WPlayer(*player);
		//ItemStack* itemStack = SymCall("?getSelectedItem@Player@@QEBAAEBVItemStack@@XZ", ItemStack*, Player*)(player);
		wp.sendText(popup(&player->getSelectedItem(), Money::getMoney(wp.getXuid()), player->getCommandPermissionLevel())
			, JUKEBOX_POPUP);
		ticks = 0;
	}
	return original(player);
}