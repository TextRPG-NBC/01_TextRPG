#pragma once

#include "Monster.h"

class Orc : public Monster
{
private:
	string name;
	int health;
	int attack;

public:
	Orc(int level);
	string getName() override;
	int getHealth() override;
	int getAttack() override;
	void takeDamage(int damage) override;
	Item* dropItem() override;
};