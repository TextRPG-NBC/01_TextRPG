#pragma once

#include "Monster.h"

class Goblin : public Monster
{
private:
	string name;
	int health;
	int attack;
	unique_ptr<IItem> item;

public:
	Goblin(int level);
	string getName() override;
	int getHealth() override;
	int getAttack() override;
	void takeDamage(int damage) override;
	unique_ptr<IItem> dropItem() override;
};