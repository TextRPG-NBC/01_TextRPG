#include <iostream>
#include <algorithm>

#include "GameManager.h"
#include "Shop.h"
#include "Player.h"
#include "Monster.h"
#include "RandomUtil.h"
#include "Constants.h"
#include "InputUtil.h"

GameManager::GameManager() : shop(std::make_unique<Shop>()), isClear(false) {}

void GameManager::run()
{
	std::string playerName;
	std::cout << "캐릭터 이름을 입력하세요 : ";
	std::getline(std::cin, playerName);
	Player& player = Player::getInstance(playerName);

	while (player.isAlive())
	{
		player.showStatus();

		battle();
		if (isClear || !player.isAlive()) break;

		//char shopChoice = inputYorN("상점에 방문하시겠습니까? (Y/N) : ");
		char shopChoice = InputUtil::getYorN("상점에 방문하시겠습니까? (Y/N): ");
		if (shopChoice == 'Y')	visitShop();
	}

	if (!player.isAlive())
	{
		std::cout << player.getName() << "가 사망했습니다. 게임오버!\n";
	}
	else if (isClear)
	{
		std::cout << "축하합니다. 게임을 클리어했습니다!\n";
	}
	else
	{
		std::cout << "[FOR DEBUG] Default : 게임을 종료합니다\n";
	}
}

void GameManager::battle()
{
	std::cout << "[전투를 시작합니다]\n";
	
	Player& player = Player::getInstance();
	std::unique_ptr<Monster> monster = generateMonster(player.getLevel());

	player.resetTempAbility();		// 버프 초기화

	if (player.hasConsumable() && RandomUtil::getInt(1, 100) <= 20)	// TODO: Constants
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
		std::cout << "보스 몬스터를 처치했습니다!\n";
		isClear = true;
		return;
	}

	int randomGold = RandomUtil::getInt(10, 20);	//TODO: Constants
	std::cout << monster->getName() << " 처치! 보상: EXP(+50), 골드(+" << randomGold << ")\n";
	player.addExp(50);			// TODO: Constants
	player.addGold(randomGold);

	if (RandomUtil::getInt(1, 100) <= 30)	// TODO: Constants
	{	// 30% 확률로 아이템 드랍(아이템 드랍 세부확률은 monster->dropItem에서 정의)
		player.addItem(monster->dropItem());
	}
}

void GameManager::visitShop()
{
	std::cout << "\n[상점에 방문했습니다]\n";
	while (true)
	{
		std::cout << "상점 메뉴:\n";
		std::cout << "1. 구매\n2.판매\n0. 나가기\n";
		int shopChoice = InputUtil::getInt("상점 메뉴를 선택해주세요: ");
		/*int shopChoice = getNumberFromUserInput("상점메뉴를 선택해주세요: ");*/
		if (shopChoice == 0)	// 상점 나가기
		{
			std::cout << "상점을 나갑니다.\n";
			break;
		}
		else if (shopChoice == 1)	// 아이템 구매
		{
			shop->buy(Player::getInstance());	
		}
		else if (shopChoice == 2)	// 아이템 판매
		{
			shop->sell(Player::getInstance());	
		}
		else
		{
			std::cout << "잘못된 입력입니다. 다시 시도해주세요.\n\n";
		}
	}
}

std::unique_ptr<Monster> GameManager::generateMonster(int playerLevel)
{
	if (playerLevel >= 10)
	{
		return std::make_unique<BossMonster>(playerLevel);
	}
	int choice = RandomUtil::getInt(1, 3/*Constant::NORMAL_MONSTER_TYPE*/);
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