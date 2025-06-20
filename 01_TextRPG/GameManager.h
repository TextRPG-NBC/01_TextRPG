#pragma once
#include <random>

/* Enum */
enum MonsterType {
	MONSTER_TYPE_GOBLIN,
	MONSTER_TYPE_ORC,
	MONSTER_TYPE_TROLL,
	MONSTER_TYPE_COUNT // Total number of monster types
};

/* Forward declaration of the Character class. */
class Monster;
class BossMonster;
class Character;

class GameManager {
private:
	std::mt19937 rng;	// Random number generator
	std::uniform_int_distribution<int> dist;	// Random number Range

public:
	/* Constructor */
	GameManager() : rng(std::random_device{}()), dist(0, MONSTER_TYPE_COUNT - 1) {}
	
	/* member methods */
	Monster* generateMonster(int level);
	BossMonster* generateBossMonster(int level);
	void battle(Character* player);
	void visitShop(Character* player);
	void displayInventory(Character* player);

};