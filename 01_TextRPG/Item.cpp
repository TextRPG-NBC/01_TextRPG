#include <iostream>
#include "Item.h"
#include "Player.h"

/* 소모품 사용 */
bool HP_Potion::use(Player& player)
{
	std::cout << "[FOR DEBUG : Item.cpp > HP_Potion::use]\n";
	if (player.getCurrentHP() == player.getMaxHP())
	{
		std::cout << "더 이상 회복할 수 없습니다. (" << player.getCurrentHP() << "/" << player.getMaxHP() << ")\n";
		return false;
	}
	player.healHP(30);	//TODO: Constants (레벨비례로 더 회복되록 하는건?)
	return true;
}

bool AttackBoost::use(Player& player)
{
	std::cout << "[FOR DEBUG : Item.cpp > AttackBoost::use]\n";
	player.addTempAttack(10);	//TODO: Constants (레벨 비례로 공격력 더 증가?)
	return true;
}

bool CriticalBoost::use(Player& player)
{
	std::cout << "[FOR DEBUG : Item.cpp > CriticalBoost::use]\n";
	player.addTempCriticalProbability(10);	//TODO: Constants
	return true;
}

std::unique_ptr<Item> Item::clone()
{
	return nullptr;
}
;