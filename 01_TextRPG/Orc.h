#pragma once

#include "Monster.h"
#include "IItem.h"
#include <memory>

class Orc : public Monster
{
private:
	string name;
	int health;
	int attack;
	unique_ptr<IItem> item;

public:
	Orc(int level);
	string getName() override;
	int getHealth() override;
	int getAttack() override;
	void takeDamage(int damage) override;
	unique_ptr<IItem> dropItem() override;
};