#pragma once
#include <memory>

#include "IArmor.h"
#include "Item.h"
#include "IWeapon.h"

class Player;
class TreeBranch : public Item, public IWeapon
{
public:
    TreeBranch() : Item(4,"나뭇가지","공격력을 5증가시킨다",15){}
    void use(Player& player) override;
    bool isConsumable() const override { return false; }
    virtual std::unique_ptr<Item> clone() override;
    virtual void equipped(Player& player) override;
    void unEquipped(Player& player) override;
};

class LeatherArmor : public Item, public IArmor
{
public:
    LeatherArmor() : Item(5,"가죽갑옷","최대체력을 10증가시킨다",15){}
    void use(Player& player) override;
    bool isConsumable() const override { return false; }
    virtual std::unique_ptr<Item> clone() override;
    virtual void equipped(Player& player) override;
    void unEquipped(Player& player) override;
};