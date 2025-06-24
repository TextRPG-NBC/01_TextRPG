#pragma once
#include <memory>
#include "Monster.h"
#include "Shop.h"


class GameManager
{
private:
	std::unique_ptr<Shop> shop;
	bool isClear;

public:
	/* Constructor */
	GameManager();

	/* Member methods */
	void run();
	void battle();
	void visitShop();
	void openInventory();
	std::unique_ptr<Monster> generateMonster(int playerLevel);
};