#include "AttackBoost.h"
#include"Character.h"

AttackBoost::AttackBoost(const std::string& name, int boostAmount, int price)
	:name(name), boostAmount(boostAmount),price(price)
{

}

void AttackBoost::use(Character* character)
{
	character->increaseAttackBoost(boostAmount);
}

std::string AttackBoost::getName() const
{
	return name;
}

int AttackBoost::getPrice() const
{
	return price;
}

int AttackBoost::getBoostAmount() const
{
	return boostAmount;
}
