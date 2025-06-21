#include "Weapon.h"
#include"Character.h"
#include<memory>
#include <iostream>
Weapon::Weapon(const std::string& name, int attackBonus, int criticalBonus, int price)
	:name(name), attackBonus(attackBonus),criticalBonus(criticalBonus),price(price)
{

}

void Weapon::use(Character* character)
{
	std::unique_ptr<Weapon> copyWeapon = std::make_unique<Weapon>(getName(), getAtttackBonus());
	character->equipWeapon(std::move(copyWeapon));
}

std::string Weapon::getName() const
{
	return name;
}

int Weapon::getPrice() const
{
	return price;
}


int Weapon::getAtttackBonus() const
{
	return attackBonus;
}

int Weapon::getCriticalBonus() const
{
	return criticalBonus;
}
