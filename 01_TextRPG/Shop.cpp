#include <iostream>
#include "Shop.h"
#include "InputUtil.h"
#include "Player.h"

Shop::Shop()
{
	std::cout << "[FOR DEBUG : Shop.cpp > Shop]\n";
	itemList.push_back(std::make_unique<HP_Potion>());
	itemList.push_back(std::make_unique<AttackBoost>());
	itemList.push_back(std::make_unique<CriticalBoost>());
}

void Shop::showItems() const
{
	std::cout << "[FOR DEBUG : Shop.cpp > showItems]\n";
	for (size_t i = 0; i < itemList.size(); ++i)
	{
		std::cout << i + 1 << ". " << itemList[i]->getName() << ", 가격: " 
			<< itemList[i]->getPrice() << "골드 / 설명 : " << itemList[i]->getDescription() << "\n";
	}
}

void Shop::buy(Player& player)
{
	std::cout << "[FOR DEBUG : Shop.cpp > buy]\n";
	showItems();	// 맞겠지?
	
	int choice = InputUtil::getInt("구매할 아이템 번호(0: 취소): ");
	if (choice == 0) return;
	else if (choice > itemList.size())
	{
		std::cout << "존재하지 않는 아이템입니다.\n";
		return;
	}

	int price = itemList[choice - 1]->getPrice();
	if (player.getGold() < price)
	{
		std::cout << "보유 골드가 부족합니다.(" << player.getGold() << "골드)\n";
		return;
	}

	player.subtractGold(price);		// NOTE: subtractGold는 Gold가 음수가 될 수 있으므로 주의
	// if(itemList[choice-1]->getName() == "HP포션")	// NOTE: itemID가 없으면 이렇게 비교해야함
	int itemId = itemList[choice - 1]->getId();
	if (itemId == 1)		// TODO: Constants(→ HP포션)
	{	// 새 객체를 생성하여 추가
		player.addItem(std::make_unique<HP_Potion>());
	}
	else if (itemId == 2)
	{
		player.addItem(std::make_unique<AttackBoost>());
	}
	else if (itemId == 3)
	{
		player.addItem(std::make_unique<CriticalBoost>());
	}
	std::cout << itemList[choice-1]->getName() << " 구매 완료\n";
}

void Shop::sell(Player& player)
{
	std::vector<std::unique_ptr<Item>>& inv = player.getInventory();
	if (inv.empty())
	{
		std::cout << "판매할 아이템이 없습니다.\n";
		return;
	}
	std::cout << "[보유 아이템]\n";
	for (size_t i = 0; i < inv.size(); ++i)
	{
		std::cout << i + 1 << ". " << inv[i]->getName() << " (판매가: " << inv[i]->getPrice() * 0.6 
			<< "골드 / 설명: " << inv[i]->getDescription() << "\n";
	}

	int choice = InputUtil::getInt("판매할 번호(0: 취소): ");
	if (choice == 0) return;
	else if (choice > inv.size())
	{
		std::cout << "존재하지 않는 아이템입니다.\n";
		return;
	}

	int price = inv[choice - 1]->getPrice();
	player.addGold(static_cast<int>(price * 0.6));	// TODO: Constants
	
	std::cout << inv[choice-1]->getName() << "판매 완료";	//
	player.removeItemByIdx(choice - 1);
}

