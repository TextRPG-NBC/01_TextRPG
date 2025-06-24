#include "Equipments.h"
#include "Player.h"


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
	player.increaseAttack(Constants::AB_TREE_BRANCH_ATK);
	player.increaseCriticalProbability(Constants::AB_TREE_BRANCH_CRI);
}

void TreeBranch::unEquipped(Player& player)
{
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
	player.increaseMaxHP(Constants::AB_LEATHER_ARMOR);
	player.increaseCurrentHP(Constants::AB_LEATHER_ARMOR);
}

void LeatherArmor::unEquipped(Player& player)
{
	player.decreaseMaxHP(Constants::AB_LEATHER_ARMOR);
}

