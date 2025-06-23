#pragma once
#include <vector>
#include <memory>
#include "Item.h"

class Player;

class Shop {
private:
	std::vector<std::unique_ptr<Item>> stock;
public:
	Shop();
	void ShowItems() const;
	void Buy(Player& p);
	void Sell(Player& p);
};
