#pragma once
#include<memory>
#include"Character.h"
#include"Weapon.h"
#include"Armor.h"
#include"AttackBoost.h"
#include"CriticalBoost.h"
#include"HealthPotion.h"


inline Character* hero()
{
	return Character::getInstance();
}

inline std::unique_ptr<Weapon> makeWeapon(const std::string& name, int attackBonus, int criticalBonus, int price)
{
	return std::make_unique<Weapon>(name, attackBonus, criticalBonus, price);
}


inline std::unique_ptr<Armor> makeArmor(const std::string& name, int maxHealthBonus, int price)
{
	return std::make_unique<Armor>(name, maxHealthBonus, price);
}


inline std::unique_ptr<AttackBoost> makeAttackBoost(const std::string& name, int attackBonus, int price)
{
	return std::make_unique<AttackBoost>(name, attackBonus, price);
}

inline std::unique_ptr<CriticalBoost> makeCriticalBoost(const std::string& name, int criticalBonus, int price)
{
	return std::make_unique<CriticalBoost>(name, criticalBonus, price);
}

inline std::unique_ptr<HealthPotion> makeHealthPotion(const std::string& name, int healAmount, int price)
{
	return std::make_unique<HealthPotion>(name, healAmount, price);
}