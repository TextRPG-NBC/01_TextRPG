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
	player.increaseAttack(10);
	player.increaseCriticalProbability(5);
}

void TreeBranch::unEquipped(Player& player)
{
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
	player.increaseMaxHP(15);
	player.increaseCurrentHP(15);
}

void LeatherArmor::unEquipped(Player& player)
{
	player.decreaseMaxHP(15);
}

