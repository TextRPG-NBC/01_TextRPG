#include<memory>
#include"HealthPotion.h"
#include"Character.h"

HealthPotion::HealthPotion(const std::string& name, int healAmount,int price)
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

std::unique_ptr<IItem> HealthPotion::clone() const
{
    return std::make_unique<HealthPotion>(getName(), getHealAmount(), getPrice());
}


int HealthPotion::getHealAmount() const
{
    return healAmount;
}
