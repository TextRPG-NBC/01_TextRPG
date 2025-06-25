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
	std::cout << "[무기 장착] : " << getName() << "을(를) 장착했습니다." << std::endl;
	std::cout << " - 공격력이 +"<< Constants::AB_TREE_BRANCH_ATK<< " 치명타 확률이 +" << Constants::AB_TREE_BRANCH_CRI << " 증가했습니다." << std::endl;
	player.increaseAttack(Constants::AB_TREE_BRANCH_ATK);
	player.increaseCriticalProbability(Constants::AB_TREE_BRANCH_CRI);
}

void TreeBranch::unEquipped(Player& player)
{
	std::cout << "[무기 탈착] : " << getName() << "을(를) 탈착했습니다." << std::endl;
	std::cout << " - 공격력이 "<< Constants::AB_TREE_BRANCH_ATK<< " 치명타 확률이 " << Constants::AB_TREE_BRANCH_CRI << " 감소했습니다." << std::endl;
	player.decreaseAttack(Constants::AB_TREE_BRANCH_ATK);
	player.decreaseCriticalProbability(Constants::AB_TREE_BRANCH_CRI);
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
	std::cout << "[방어구 장착] : " << getName() << "을(를) 장착했습니다." << std::endl;
	std::cout << " - 최대 체력이 +" << Constants::AB_LEATHER_ARMOR << " 증가했습니다." << std::endl;
	player.increaseMaxHP(Constants::AB_LEATHER_ARMOR);
	player.increaseCurrentHP(Constants::AB_LEATHER_ARMOR);
}

void LeatherArmor::unEquipped(Player& player)
{
	std::cout << "[방어구 탈착] : " << getName() << "을(를) 탈착했습니다." << std::endl;
	std::cout << " - 최대 체력이 " << Constants::AB_LEATHER_ARMOR << " 감소했습니다." << std::endl;
	player.decreaseMaxHP(Constants::AB_LEATHER_ARMOR);
}

