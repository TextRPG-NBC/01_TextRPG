#pragma once
#include <string>
#include <memory>

class Player;
class Item;

class Monster
{
protected:
	std::string name;
	int level, maxHP, curHP, attack;
	bool isBoss;
public:
	/* Constructor */
	Monster(const std::string& name, int level, int hp, int attack, bool isBoss);
	
	/* Destructor */
	virtual ~Monster() = default;

	/* Member methods */
	virtual void takeDamage(int damage);
	virtual void attackPlayer(Player& player);
	virtual std::unique_ptr<Item> dropItem();
	bool isAlive() const;
	bool isBossMonster() const { return isBoss; };
	std::string getName() const;
	int getHP() const;			// 사용한적 없음
	int getLevel() const;		// 사용한적 없음
};

/* Derived Classes */
class Goblin : public Monster
{
public:
	Goblin(int playerLevel);
};

class Orc : public Monster {
public:
	Orc(int playerLevel);
};

class Troll : public Monster {
public:
	Troll(int playerLevel);
};

class BossMonster : public Monster {
public:
	BossMonster(int playerLevel);
};
