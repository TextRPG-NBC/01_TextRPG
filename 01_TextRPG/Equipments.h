#pragma once
#include <memory>

#include "IArmor.h"
#include "Item.h"
#include "IWeapon.h"

class Player;
class TreeBranch : public Item, public IWeapon
{
public:
    TreeBranch() : Item(Constants::TREE_BRANCH, "나뭇가지",
        "공격력을 5증가시킨다", Constants::PRICE_TREE_BRANCH){}
    bool use(Player& player) override;
    bool isConsumable() const override { return false; }
    virtual std::unique_ptr<Item> clone() override;
    virtual void equipped(Player& player) override;
    void unEquipped(Player& player) override;
};

class LeatherArmor : public Item, public IArmor
{
public:
    LeatherArmor() : Item(Constants::LEATHER_ARMOR, "가죽갑옷",
        "최대체력을 10증가시킨다", Constants::PRICE_LEATHER_ARMOR){}
    bool use(Player& player) override;
    bool isConsumable() const override { return false; }
    virtual std::unique_ptr<Item> clone() override;
    virtual void equipped(Player& player) override;
    void unEquipped(Player& player) override;
};