#pragma once

#include <string>

using namespace std;

class IItem;
class ItemManager;

class Monster abstract
{

public:
	virtual string getName() abstract;
	virtual int getHealth() abstract;
	virtual int getAttack() abstract;
	virtual void takeDamage(int damage) abstract;
	virtual unique_ptr<IItem> dropItem() abstract;
	virtual ~Monster() = default;
};