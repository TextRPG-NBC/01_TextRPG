#pragma once
#include <random>

/* Enum */
enum MonsterType 
{
	MONSTER_TYPE_GOBLIN,
	MONSTER_TYPE_ORC,
	MONSTER_TYPE_TROLL,
	MONSTER_TYPE_COUNT // Total number of monster types
};

enum ItemType 
{
	ITEM_TYPE_HealthPotion,
	ITEM_TYPE_AttackBoost,
	ITEM_TYPE_CriticalBoost,
	ITEM_TYPE_COUNT // Total number of item types
};

/* Forward declaration of the Character class. */
class Monster;
class BossMonster;
class Character;
class Item;

class GameManager
{
private:
	std::mt19937 rng;	// Random number generator
	std::uniform_int_distribution<int> monsterDist;	// Random Monster(0 ~ MONSTER_TYPE_COUNT)
	std::uniform_int_distribution<int> goldDist;	// Random Gold(10 ~ 20)
	std::uniform_int_distribution<int> itemDist;	// Random Item(0 ~ ITEM_TYPE_COUNT)
	std::uniform_int_distribution<int> basicDist;	// Random Gold(0 ~ 99)

public:
	/* Constructor */
	GameManager() : rng(std::random_device{}()), monsterDist(0, MONSTER_TYPE_COUNT-1), goldDist(10, 20), itemDist(0, ITEM_TYPE_COUNT-1), basicDist(0, 99) {}
	
	/* member methods */
	Monster* generateMonster(int level);
	BossMonster* generateBossMonster(int level);
	void battle(Character* player);
	void visitShop(Character* player);
	void displayInventory(Character* player);

	Item* dropRandomItem();
	char inputYorN(const std::string& prompt);
};