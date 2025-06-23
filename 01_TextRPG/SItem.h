#pragma once
#include"Weapon.h"
#include"Armor.h"
#include"AttackBoost.h"
#include"CriticalBoost.h"
#include"MaxHealthBoost.h"
#include"HealthPotion.h"

inline std::unique_ptr<Weapon> makeWeapon(const std::string& name = "나뭇가지", int attackBonus = 5, int criticalBonus = 2, int price = 1)
{
	return std::make_unique<Weapon>(name, attackBonus, criticalBonus, price);
}

inline std::unique_ptr<Armor> makeArmor(const std::string& name = "누더기 천 조각", int maxHealthBonus = 10, int price = 1)
{
	return std::make_unique<Armor>(name, maxHealthBonus, price);
}

inline std::unique_ptr<AttackBoost> makeAttackBoost(const std::string& name = "하급 공격력 영약", int boostAmount = 5, int price = 1)
{
	return std::make_unique<AttackBoost>(name, boostAmount, price);
}

inline std::unique_ptr<CriticalBoost> makeCriticalBoost(const std::string& name = "하급 치명타 영약", int boostAmount = 5, int price = 1)
{
	return std::make_unique<CriticalBoost>(name, boostAmount, price);
}

inline std::unique_ptr<MaxHealthBoost> makeMaxHealthBoost(const std::string& name = "하급 체력 영약", int boostAmount = 5, int price = 1)
{
	return std::make_unique<MaxHealthBoost>(name, boostAmount, price);
}

inline std::unique_ptr<HealthPotion> makeHealthPotion(const std::string& name = "소량의 회복 물약", int healAmount = 10, int price = 1)
{
	return std::make_unique<HealthPotion>(name, healAmount, price);
}