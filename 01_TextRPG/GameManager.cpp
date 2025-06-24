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
	std::string playerName = InputUtil::getStr("▶ 플레이어를 생성합니다. 이름을 입력하세요: ");
	Player& player = Player::getInstance(playerName);
	

	while (player.isAlive())
	{
		player.showStatus();

		battle();
		player.resetTempAbility();		// 전투 후 버프 초기화

		if (isClear || !player.isAlive()) break;

		player.showStatus();
		char shopChoice = InputUtil::getYorN("▶ 상점에 방문하시겠습니까? (Y/N): ");
		if (shopChoice == 'Y')	visitShop();
		system("cls");

	}

	if (!player.isAlive())
	{
		std::cout << "[전투패배] : \"" << player.getName() << "\"이(가) 사망했습니다. 게임오버!\n";
	}
	//else if (isClear)
	//{
	//	// 게임클리어
	//}
	//else
	//{
	//	//// std::cout << "[FOR DEBUG] Default : 게임을 종료합니다\n";
	//}
	std::cout << "[게임종료] : ... 게임을 종료합니다 ...\n";
}

void GameManager::battle()
{
	std::cout << "\n▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼[전투를 시작합니다]▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼\n";
	system("pause");
	std::cout << "\n";
	
	Player& player = Player::getInstance();
	std::unique_ptr<Monster> monster = generateMonster(player.getLevel());

	

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
		std::cout << "[★ 게임 클리어 ★] : 축하합니다. 보스 몬스터 \"" << monster->getName() << "\"을(를) 처치하고 게임을 클리어했습니다!\n";
		isClear = true;
		return;
	}
	
	int randomGold = RandomUtil::getInt(Constants::MIN_DROP_GOLD, Constants::MAX_DROP_GOLD);	// 10 ~ 20
	player.addExp(Constants::DROP_EXP);		// 50
	player.addGold(randomGold);
	std::cout << "[전투 승리] : " << monster->getName() << " 처치!\n";
	std::cout << " ☞ \"" << player.getName() << "\"이(가) EXP(+50), 골드(+" << randomGold << ")를 획득했습니다.(레벨: " << player.getLevel() << ", EXP(" << player.getExp() << "/100), 골드: " << player.getGold() << ")\n";

	if (RandomUtil::getInt(1, 100) <= Constants::P_DROP_ITEM)	// 30
	{
		player.addItem(monster->dropItem());
	}
	std::cout << "\n▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲[전투를 종료합니다]▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲\n\n";
}

void GameManager::visitShop()
{
	/*system("cls");
	std::cout << "[상점에 방문했습니다]\n";*/
	while (true)
	{
		system("cls");
		PrintUtil::printShopMenu();
		int shopChoice = InputUtil::getInt("▶ 상점 메뉴를 선택해주세요: ");
		if (shopChoice == Constants::EXIT)			// 0
		{
			break;
		}
		else if (shopChoice == Constants::BUY)		// 1
		{
			system("cls");
			shop->buy(Player::getInstance());	
		}
		else if (shopChoice == Constants::SELL)		// 2
		{
			system("cls");
			shop->sell(Player::getInstance());	
		}
		else if (shopChoice == Constants::STATUS)	// 3
		{	
			system("cls");
			openInventory();
		}
		else
		{
			std::cout << "잘못된 입력입니다. 메뉴의 숫자를 입력해주세요.\n\n";
			system("pause");
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
		system("pause");
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
		player.showStatus();
		system("pause");
	}
	else {
		std::cout << "잘못된 입력입니다. 아이템의 숫자를 입력해주세요.\n";
		system("pause");
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