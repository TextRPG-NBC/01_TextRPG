#include <iostream>
#include "Item.h"
#include "Player.h"

/* 소모품 사용 */
bool HP_Potion::use(Player& player)
{
	// std::cout << "[FOR DEBUG : Item.cpp > HP_Potion::use]\n";
	if (player.getCurrentHP() == player.getMaxHP())
	{
		std::cout << "더 이상 회복할 수 없습니다. (" << player.getCurrentHP() << "/" << player.getMaxHP() << ")\n";
		return false;
	}
	player.healHP(Constants::AB_HP_POTION);
	return true;
}

bool AttackBoost::use(Player& player)
{
	// std::cout << "[FOR DEBUG : Item.cpp > AttackBoost::use]\n";
	player.addTempAttack(Constants::AB_ATTACK_BOOST);
	return true;
}

bool CriticalBoost::use(Player& player)
{
	// std::cout << "[FOR DEBUG : Item.cpp > CriticalBoost::use]\n";
	player.addTempCriticalProbability(Constants::AB_CRITICAL_BOOST);	//TODO: Constants
	return true;
}

std::unique_ptr<Item> Item::clone()
{
	return nullptr;
}
;