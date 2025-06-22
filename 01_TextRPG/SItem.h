#pragma once
#include<memory>
#include<string>

class Weapon;
class Armor;
class AttackBoost;
class CriticalBoost;
class MaxHealthBoost;
class HealthPotion;

std::unique_ptr<Weapon> makeWeapon(const std::string& name, int attackBonus, int criticalBonus, int price);

std::unique_ptr<Armor> makeArmor(const std::string& name, int maxHealthBonus, int price);

std::unique_ptr<AttackBoost> makeAttackBoost(const std::string& name, int attackBonus, int price);

std::unique_ptr<CriticalBoost> makeCriticalBoost(const std::string& name, int criticalBonus, int price);

std::unique_ptr<MaxHealthBoost> makeMaxHealthBoost(const std::string& name, int maxHealthBonus, int price);

std::unique_ptr<HealthPotion> makeHealthPotion(const std::string& name, int healAmount, int price);
