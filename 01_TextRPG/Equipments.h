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
        "영구히 공격력이 +" + std::to_string(Constants::AB_TREE_BRANCH_ATK) + 
        ", 치명타 확률이 +" + std::to_string(Constants::AB_TREE_BRANCH_CRI) +" 증가합니다", Constants::PRICE_TREE_BRANCH){}
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
	    "영구히 최대 체력이 +" + std::to_string(Constants::AB_LEATHER_ARMOR) + " 증가합니다", Constants::PRICE_TREE_BRANCH){}
    bool use(Player& player) override;
    bool isConsumable() const override { return false; }
    virtual std::unique_ptr<Item> clone() override;
    virtual void equipped(Player& player) override;
    void unEquipped(Player& player) override;
};