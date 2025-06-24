#include <iostream>
#include "Item.h"
#include "Player.h"

/* 소모품 사용 */
void HP_Potion::use(Player& player)
{
	std::cout << "[FOR DEBUG : Item.cpp > HP_Potion::use]\n";
	player.healHP(30);	//TODO: Constants (레벨비례로 더 회복되록 하는건?)
}

void AttackBoost::use(Player& player)
{
	std::cout << "[FOR DEBUG : Item.cpp > AttackBoost::use]\n";
	player.addTempAttack(10);	//TODO: Constants (레벨 비례로 공격력 더 증가?)
}

void CriticalBoost::use(Player& player)
{
	std::cout << "[FOR DEBUG : Item.cpp > CriticalBoost::use]\n";
	player.addTempCriticalProbability(10);	//TODO: Constants
}

std::unique_ptr<Item> Item::clone()
{
	return nullptr;
}
;