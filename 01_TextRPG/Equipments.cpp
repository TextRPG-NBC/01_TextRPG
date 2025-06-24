#include "Equipments.h"
#include "Player.h"
#include<iostream>

bool TreeBranch::use(Player& player)
{
	player.equipWeapon(this->clone());
	return true;
}

std::unique_ptr<Item> TreeBranch::clone()
{
	return std::make_unique<TreeBranch>(*this);
}

void TreeBranch::equipped(Player& player)
{
	std::cout << getName() << "을(를) 장착했습니다." << std::endl;
	std::cout << "공격력이 10, 치명타율이 5 증가했습니다." << std::endl;
	player.increaseAttack(10);
	player.increaseCriticalProbability(5);
}

void TreeBranch::unEquipped(Player& player)
{
	std::cout << getName() << "을(를) 탈착했습니다." << std::endl;
	std::cout << "공격력이 10, 치명타율이 5 감소했습니다." << std::endl;
	player.decreaseAttack(10);
	player.decreaseCriticalProbability(5);
}

bool LeatherArmor::use(Player& player)
{
	player.equipArmor(this->clone());
	return true;
}

std::unique_ptr<Item> LeatherArmor::clone()
{
	return std::make_unique<LeatherArmor>(*this);
}

void LeatherArmor::equipped(Player& player)
{
	std::cout << getName() << "을(를) 장착했습니다." << std::endl;
	std::cout << "최대 체력이 15 증가했습니다." << std::endl;
	player.increaseMaxHP(15);
	player.increaseCurrentHP(15);
}

void LeatherArmor::unEquipped(Player& player)
{
	std::cout << getName() << "을(를) 탈착했습니다." << std::endl;
	std::cout << "최대 체력이 15 감소했습니다." << std::endl;

	player.decreaseMaxHP(15);
}

