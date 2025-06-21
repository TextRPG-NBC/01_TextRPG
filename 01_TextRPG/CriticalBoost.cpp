#include "CriticalBoost.h"
#include"Character.h"

CriticalBoost::CriticalBoost(const std::string& name, int boostAmount, int price)
	:name(name), boostAmount(boostAmount), price(price)
{
}

void CriticalBoost::use(Character* character)
{
	character->increaseCriticalBoost(boostAmount);
}

std::string CriticalBoost::getName() const
{
	return name;
}

int CriticalBoost::getPrice() const
{
	return price;
}

int CriticalBoost::getBoostAmount()const
{
	return boostAmount;
}