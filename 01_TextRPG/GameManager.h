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

public:
	/* Constructor */
	GameManager(){}
	
	/* member methods */
	std::unique_ptr<Monster> generateMonster(int level);
	std::unique_ptr<Monster> generateBossMonster(int level);	// generate Monster에 다 넣으면 안되나? 10레벨 되면 자동생성인데;;
	void battle(Character* player);
	void visitShop(Character* player);
	void displayInventory(Character* player);

	Item* dropRandomItem();
	char inputYorN(const std::string& prompt);
};