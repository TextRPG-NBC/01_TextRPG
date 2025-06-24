#include <iostream>
#include <algorithm>

#include "GameManager.h"
#include "Shop.h"
#include "Player.h"
#include "Monster.h"
#include "RandomUtil.h"
#include "Constants.h"
#include "InputUtil.h"
#include "PrintUtil.h"

GameManager::GameManager() : shop(std::make_unique<Shop>()), isClear(false) {}

void GameManager::run()
{
	std::string playerName;
	std::cout << "▶ 플레이어를 생성합니다. 이름을 입력하세요: ";
	std::getline(std::cin, playerName);
	Player& player = Player::getInstance(playerName);

	while (player.isAlive())
	{
		player.showStatus();

		battle();
		if (isClear || !player.isAlive()) break;

		char shopChoice = InputUtil::getYorN("▶ 상점에 방문하시겠습니까? (Y/N): ");
		if (shopChoice == 'Y')	visitShop();


	}

	if (!player.isAlive())
	{
		std::cout << player.getName() << "(이)가 사망했습니다. 게임오버!\n";
	}
	else if (isClear)
	{
		// 게임클리어
	}
	else
	{
		std::cout << "[FOR DEBUG] Default : 게임을 종료합니다\n";
	}
}

void GameManager::battle()
{
	std::cout << "\n[전투를 시작합니다]\n";
	system("pause");
	
	Player& player = Player::getInstance();
	std::unique_ptr<Monster> monster = generateMonster(player.getLevel());

	player.resetTempAbility();		// 버프 초기화

	if (player.hasConsumable() && RandomUtil::getInt(1, 100) <= Constants::P_USE_ITEM)
	{
		player.useItem();			// 20% 확률로 아이템 사용	
	}

	while (monster->isAlive() && player.isAlive())	// 일기토
	{
		player.attackMonster(*monster);
		if (!monster->isAlive())	break;
		monster->attackPlayer(player);
	}

	if (!player.isAlive()) return;	// 플레이어 사망시
	if (monster->isBossMonster())	// 보스몬스터 처치시
	{
		std::cout << "축하합니다. 보스 몬스터 [" << monster->getName() << "](을)를 처치하고 게임을 클리어했습니다!\n";
		isClear = true;
		return;
	}

	int randomGold = RandomUtil::getInt(Constants::MIN_DROP_GOLD, Constants::MAX_DROP_GOLD);	// 10 ~ 20
	player.addExp(Constants::DROP_EXP);		// 50
	player.addGold(randomGold);
	std::cout << monster->getName() << " 처치!";
	std::cout << player.getName() << "(이)가 EXP(+50), 골드(+" << randomGold << ")를 획득했습니다.(레벨: " << player.getLevel() << "(" << player.getExp() << "/100), 골드: " << player.getGold() << ")\n";

	if (RandomUtil::getInt(1, 100) <= Constants::P_DROP_ITEM)	// 30
	{
		player.addItem(monster->dropItem());
	}
	std::cout << "[전투를 종료합니다]\n\n";
}

void GameManager::visitShop()
{
	system("cls");
	std::cout << "[상점에 방문했습니다]\n";
	while (true)
	{
		PrintUtil::printShopMenu();
		int shopChoice = InputUtil::getInt("▶ 상점 메뉴를 선택해주세요: ");
		if (shopChoice == Constants::EXIT)			// 0
		{
			std::cout << "상점을 나갑니다.\n";
			break;
		}
		else if (shopChoice == Constants::BUY)		// 1
		{
			shop->buy(Player::getInstance());	
		}
		else if (shopChoice == Constants::SELL)		// 2
		{
			shop->sell(Player::getInstance());	
		}
		else if (shopChoice == Constants::STATUS)	// 3
		{	
			openInventory();
		}
		else
		{
			std::cout << "잘못된 입력입니다. 다시 시도해주세요.\n\n";
		}
	}
}

void GameManager::openInventory()
{
	Player& player = Player::getInstance();
	player.showStatus();
	if (player.getInventory().empty())
	{
		std::cout << "인벤토리가 비어있습니다.\n";
		return;
	}
	player.displayInventory();

	int inventoryChoice = InputUtil::getInt("▶ 사용할 아이템 숫자를 입력해주세요(0: 취소): ");
	if (inventoryChoice == 0)
	{
		return;
	}
	else if (inventoryChoice <= player.getInventory().size())
	{
		player.useItemUsingIndex(inventoryChoice - 1);
	}
	else {
		std::cout << "잘못된 입력입니다. \n";
	}

}

std::unique_ptr<Monster> GameManager::generateMonster(int playerLevel)
{
	if (playerLevel >= Constants::MAX_LEVEL)	// 10
	{
		return std::make_unique<BossMonster>(playerLevel);
	}
	int choice = RandomUtil::getInt(1, Constants::NORMAL_MONSTER_TYPE);	// 3
	switch (choice)
	{
	case Constants::GOBLIN:
		return std::make_unique<Goblin>(playerLevel);
	case Constants::ORC:
		return std::make_unique<Orc>(playerLevel);
	case Constants::TROLL:
		return std::make_unique<Troll>(playerLevel);
	default:
		return std::make_unique<Goblin>(playerLevel);
	}
}