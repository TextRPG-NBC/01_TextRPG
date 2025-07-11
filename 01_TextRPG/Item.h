﻿#pragma once
#include <string>

#include"IWeapon.h"
#include <memory>

#include "Constants.h"


#include "IArmor.h"
class Player;
class Item
{
protected:
	int id;
	std::string name;
	std::string description;
	int price;

public:
	/* Constructor */
	Item(int id, const std::string& name, const std::string& description, int price)
		: id(id), name(name), description(description), price(price) {}
	
	/* Destructor */
	virtual ~Item() = default;

	/* Member methods */
	virtual bool use(Player& player) = 0;
	virtual bool isConsumable() const = 0;
	virtual std::unique_ptr<Item> clone();
	std::string getName() const { return name; }
	std::string getDescription() const { return description; }
	int getPrice() const { return price; }
	int getId() const { return id; }
};

/* Derived Classes */
class HP_Potion : public Item 
{
public:
	HP_Potion() : Item(Constants::HP_POTION, "HP포션", 
		"체력을 +" + std::to_string(Constants::AB_HP_POTION) + " 회복합니다", 
		Constants::PRICE_HP_POTION) {}
	bool use(Player& player) override;
	bool isConsumable() const override { return true; }
};

class AttackBoost : public Item
{
public:
	AttackBoost() : Item(Constants::ATTACK_BOOST, "힘의 영약", 
		"이번 전투동안 공격력이 +" + std::to_string(Constants::AB_ATTACK_BOOST) + " 증가합니다", 
		Constants::PRICE_ATTACK_BOOST) {}
	bool use(Player& player) override;	
	bool isConsumable() const override { return true; }
};

class CriticalBoost : public Item
{
public:
	CriticalBoost() : Item(Constants::CRITICAL_BOOST, "치명타 확률 영약", 
		"이번 전투동안 치명타확률이 +" + std::to_string(Constants::AB_CRITICAL_BOOST) + " 증가합니다", 
		Constants::PRICE_CRITICAL_BOOST) {}
	bool use(Player& player) override;
	bool isConsumable() const override { return true; }
};