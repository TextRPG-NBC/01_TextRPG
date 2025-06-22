#include "Armor.h"
#include"Character.h"
Armor::Armor(const std::string& name, int maxHealthBonus, int price)
    :name(name), maxHealthBonus(maxHealthBonus),price(price)
{
}

void Armor::use(Character* character)
{
    std::unique_ptr<Armor> copyArmor = std::make_unique<Armor>(getName(), getMaxHealthBonus(),getPrice());
    character->equipArmor(std::move(copyArmor));
}

std::string Armor::getName() const
{
    return name;
}

int Armor::getPrice() const
{
    return price;
}

int Armor::getMaxHealthBonus() const
{
    return maxHealthBonus;
}
