#include<memory>
#include"MaxHealthBoost.h"
#include"Character.h"

MaxHealthBoost::MaxHealthBoost(const std::string& name, int boostAmount,int price)
	:name(name),boostAmount(boostAmount),price(price)
{
}

void MaxHealthBoost::use(Character* character)
{
	character->increaseMaxHealthBoost(boostAmount);
}

std::string MaxHealthBoost::getName() const
{
	return name;
}

int MaxHealthBoost::getPrice() const
{
	return price;
}

std::unique_ptr<IItem> MaxHealthBoost::clone() const
{
	return std::make_unique<MaxHealthBoost>(getName(), getBoostAmount(), getPrice());
}


int MaxHealthBoost::getBoostAmount() const
{
	return boostAmount;
}
