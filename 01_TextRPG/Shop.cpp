#include <iostream>
#include "Shop.h"
#include "InputUtil.h"
#include "Player.h"
#include "Constants.h"
#include "Equipments.h"

Shop::Shop()
{
	// std::cout << "[FOR DEBUG : Shop.cpp > Shop]\n";
	itemList.push_back(std::make_unique<HP_Potion>());
	itemList.push_back(std::make_unique<AttackBoost>());
	itemList.push_back(std::make_unique<CriticalBoost>());
	itemList.push_back(std::make_unique<TreeBranch>());
	itemList.push_back(std::make_unique<LeatherArmor>());
}

void Shop::showItems() const
{
	// std::cout << "[FOR DEBUG : Shop.cpp > showItems]\n";
	std::cout << "\n\n\n----------------[ 상점 아이템 목록 ]----------------\n|\n";
	for (size_t i = 0; i < itemList.size(); ++i)
	{
		std::cout << "| " << i + 1 << ". " << itemList[i]->getName() << "(" <<
			itemList[i]->getPrice() << "골드): " << itemList[i]->getDescription() << "\n";
	}
	std::cout << "|\n----------------------------------------------------\n";
}

void Shop::buy(Player& player)
{
	// std::cout << "[FOR DEBUG : Shop.cpp > buy]\n";
	showItems();
	std::cout << "(소지금: " << player.getGold() << "골드)\n";
	
	int choice = InputUtil::getInt("▶ 구매할 아이템 번호(0: 취소): ");
	if (choice == 0) return;
	else if (choice > itemList.size())
	{
		std::cout << "올바른 번호를 입력해주세요.\n";
		return;
	}

	int price = itemList[choice - 1]->getPrice();
	if (player.getGold() < price)
	{
		std::cout << "보유 골드가 부족합니다.(소지금: " << player.getGold() << "골드)\n";
		return;
	}

	player.subtractGold(price);		// NOTE: subtractGold는 Gold가 음수가 될 수 있으므로 주의
	int itemId = itemList[choice - 1]->getId();
	if (itemId == Constants::HP_POTION)				// 1
	{	// 새 객체를 생성하여 추가
		player.addItem(std::make_unique<HP_Potion>());
	}
	else if (itemId == Constants::ATTACK_BOOST)		// 2
	{
		player.addItem(std::make_unique<AttackBoost>());
	}
	else if (itemId == Constants::CRITICAL_BOOST)	// 3
	{
		player.addItem(std::make_unique<CriticalBoost>());
	}
	else if (itemId == Constants::TREE_BRANCH)
	{
		player.addItem(std::make_unique<TreeBranch>());
	}
	else if (itemId == Constants::LEATHER_ARMOR)
	{
		player.addItem(std::make_unique<LeatherArmor>());
	}
	std::cout << "[아이템 구매] : \"" << itemList[choice - 1]->getName() << "\" 구매 완료(소지금: " << player.getGold() << ")\n";
}

void Shop::sell(Player& player)
{
	std::vector<std::unique_ptr<Item>>& inv = player.getInventory();
	if (inv.empty())
	{
		std::cout << "판매할 아이템이 없습니다.\n";
		return;
	}

	std::cout << "\n\n\n---------------[ 보유 아이템 목록 ]-----------------\n|\n";
	for (size_t i = 0; i < inv.size(); ++i)
	{
		std::cout << "| " << i + 1 << ". " << inv[i]->getName() << "(" << inv[i]->getPrice() * Constants::SELL_RATE /*= 0.6*/
			<< "골드): " << inv[i]->getDescription() << "\n";
	}
	std::cout << "|\n----------------------------------------------------\n";
	std::cout << "(소지금: " << player.getGold() << "골드)\n";

	int choice = InputUtil::getInt("▶ 판매할 아이템 번호(0: 취소): ");
	if (choice == 0) return;
	else if (choice > inv.size())
	{
		std::cout << "올바른 번호를 입력해주세요.\n";
		return;
	}

	int price = inv[choice - 1]->getPrice();
	player.addGold(static_cast<int>(price * Constants::SELL_RATE));	// 0.6f
	
	std::cout << "[아이템 판매] \"" << inv[choice - 1]->getName() << "\" 판매 완료(소지금: " << player.getGold() << ")\n";
	player.removeItemByIdx(choice - 1);
}

