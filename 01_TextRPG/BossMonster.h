#pragma once

#include "Monster.h"

class BossMonster : public Monster
{
private:
	string name;
	int health;
	int attack;
	unique_ptr<IItem> item;

public:
	BossMonster(int level);
	string getName() override;
	int getHealth() override;
	int getAttack() override;
	void takeDamage(int damage) override;
	unique_ptr<IItem> dropItem() override;
};