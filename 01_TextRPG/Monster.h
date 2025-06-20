#pragma once

#include <string>

using namespace std;

class Item;

class Monster abstract
{

public:
	virtual string getName() abstract;
	virtual int getHealth() abstract;
	virtual int getAttack() abstract;
	virtual void takeDamage(int damage) abstract;
	virtual Item* dropItem() abstract;
	virtual ~Monster() = default;
};