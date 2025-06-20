#pragma once

#include "Monster.h"

class Troll : public Monster
{
private:
	string name;
	int health;
	int attack;

public:
	string getName() override;
	int getHealth() override;
	int getAttack() override;
	void takeDamage(int damage) override;
	Item* dropItem() override;
};