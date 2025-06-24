#include <iostream>
#include "Item.h"
#include "Player.h"

/* 소모품 사용 */
bool HP_Potion::use(Player& player)
{
	// std::cout << "[FOR DEBUG : Item.cpp > HP_Potion::use]\n";
	if (player.getCurrentHP() == player.getMaxHP())
	{
		std::cout << "[아이템 사용 실패] : 더 이상 회복할 수 없습니다. (" << player.getCurrentHP() << "/" << player.getMaxHP() << ")\n";
		return false;
	}
	std::cout << "[아이템 사용] : " << name << "을(를) 사용했습니다.\n";
	std::cout << " - ";
	player.healHP(Constants::AB_HP_POTION);
	return true;
}

bool AttackBoost::use(Player& player)
{
	// std::cout << "[FOR DEBUG : Item.cpp > AttackBoost::use]\n";
	std::cout << "[아이템 사용] : " << name << "을(를) 사용했습니다.\n";
	std::cout << " - 이번 전투동안 ";
	player.addTempAttack(Constants::AB_ATTACK_BOOST);
	return true;
}

bool CriticalBoost::use(Player& player)
{
	// std::cout << "[FOR DEBUG : Item.cpp > CriticalBoost::use]\n";
	std::cout << "[아이템 사용] : " << name << "을(를) 사용했습니다.\n";
	std::cout << " - 이번 전투동안 ";
	player.addTempCriticalProbability(Constants::AB_CRITICAL_BOOST);
	return true;
}

std::unique_ptr<Item> Item::clone()
{
	return nullptr;
}
;