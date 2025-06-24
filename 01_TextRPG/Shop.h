#pragma once
#include <vector>
#include <memory>
#include "Item.h"

class Shop
{
private:
	std::vector<std::unique_ptr<Item>> itemList;

public:
	/* Constructor */
	Shop();

	/* Member methods */
	void showItems() const;
	void buy(Player& player);
	void sell(Player& player);
};