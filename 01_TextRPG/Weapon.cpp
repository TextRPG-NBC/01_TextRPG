#include<memory>
#include"Weapon.h"
#include"Character.h"

Weapon::Weapon(const std::string& name, int attackBonus, int criticalBonus, int price)
	:name(name), attackBonus(attackBonus),criticalBonus(criticalBonus),price(price)
{

}

void Weapon::use(Character* character)
{
	std::unique_ptr<Weapon> copyWeapon = std::make_unique<Weapon>(getName(), getAttackBonus(),getCriticalBonus(),getPrice());
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

std::unique_ptr<IItem> Weapon::clone() const
{
	return std::make_unique<Weapon>(getName(), getAttackBonus(), getCriticalBonus(), getPrice());
}

int Weapon::getAttackBonus() const
{
	return attackBonus;
}

int Weapon::getCriticalBonus() const
{
	return criticalBonus;
}
