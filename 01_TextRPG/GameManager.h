#pragma once
#include <random>

/* Forward declaration of the Character class. */
class Monster;

class GameManager
{
private:
	std::unique_ptr<Shop> shop;
public:
	/* Constructor */
	GameManager() : shop(std::make_unique<Shop>()){}
	
	/* member methods */
	std::unique_ptr<Monster> generateMonster(int level);
	std::unique_ptr<Monster> generateBossMonster(int level);	// generate Monster에 다 넣으면 안되나? 10레벨 되면 자동생성인데;;
	void run();
	void battle();
	void visitShop();
	int getNumberFromUserInput(const std::string& prompt);
	char inputYorN(const std::string& prompt);
};