#include "HealthPotion.h"
#include "Character.h"

#include<iostream>
HealthPotion::HealthPotion(const std::string name, int healAmount,int price)
    : name(name), healAmount(healAmount), price(price)
{
}

void HealthPotion::use(Character* character)
{
    character->recovery(healAmount);
}

std::string HealthPotion::getName() const
{
    return name;
}

int HealthPotion::getPrice() const
{
    return price;
}

int HealthPotion::getHealAmount() const
{
    return healAmount;
}
