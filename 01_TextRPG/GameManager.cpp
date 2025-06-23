#include "GameManager.h"
#include "Constants.h"
#include "RandomUtil.h"
#include "Character.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "BossMonster.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include "Shop.h"

/* 랜덤 일반 몬스터 생성, 반환(unique_ptr) */
std::unique_ptr<Monster> GameManager::generateMonster(int level)
{
	int choice = RandomUtil::getInt(0, 2/*Constants::MONSTER_TYPE_COUNT*/);
	switch (choice)
	{
	case Constants::GOBLIN:
		return std::make_unique<Goblin>(level);
	case Constants::ORC:
		return std::make_unique<Orc>(level);
	case Constants::TROLL:
		return std::make_unique<Troll>(level);
	default:
		return std::make_unique<Goblin>(level);
	}
}

/* 보스 몬스터 생성, 반환(unique_ptr) */
std::unique_ptr<Monster> GameManager::generateBossMonster(int level)
{
	return std::make_unique<BossMonster>(level);
}

/* y or n 입력 */
char GameManager::inputYorN(const std::string& prompt = "Y 또는 N을 입력하세요 : ")
{
	std::string answer;
	while (true)
	{
		std::cout << prompt;
		if (!std::getline(std::cin, answer))	// 입력 오류 발생시
		{
			std::cin.clear();			// 입력 스트림 초기화
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 버퍼 비우기
			std::cout << "입력 오류가 발생했습니다. 다시 시도해주세요." << std::endl;
			continue;				// 다시 입력 받기
		}

		// 대소문자 무시, 공백 제거
		answer.erase(remove_if(answer.begin(), answer.end(), ::isspace), answer.end());
		std::transform(answer.begin(), answer.end(), answer.begin(), ::toupper);

		if (answer == "Y" || answer == "YES") { return 'Y'; }
		else if (answer == "N" || answer == "NO") { return 'N'; }
		else{ std::cout << "잘못된 입력입니다. Y 또는 N만 입력해주세요." << std::endl; }
	}
}

/* 게임 시작 */
void GameManager::run()
{
	std::string playerName;
	std::cout << "플레이어 이름을 입력하세요: ";
	std::cin >> playerName;
	Character* player = Character::getInstance(playerName);	// TODO: playerName 들어가도록 getInstance 수정
	while (!player->getIsDead())
	{
		player->displayStatus();

		battle();
		if (!player->getIsDead())	break;

		char shopChoice = inputYorN("상점에 방문하시겠습니까? (Y/N)\n");
		if (shopChoice == 'Y')	visitShop();
	}

	if (!player->getIsDead())
	{
		std::cout << "게임 클리어!\n";
		return;
	}
	std::cout << player->getName() << "가 사망했습니다. 게임 오버!\n";
}


/* 몬스터 VS 플레이어 전투시작 */
void GameManager::battle()
{
	printf("[전투를 시작합니다]\n");

	Character* player = Character::getInstance();
	std::unique_ptr<Monster> newMonster;
	if (player->getLevel() < 10 /*MAX_LEVEL*/)		// 플레이어 레벨에 맞는 몬스터 생성
	{
		newMonster = generateMonster(player->getLevel());
	}
	else 
	{
		newMonster = generateBossMonster(player->getLevel());
	}

	while (!player->getIsDead() && newMonster->getHealth() > 0)
	{
		if (RandomUtil::getInt(0, 99) < 20)			// 20% 확률로 랜덤 아이템 사용
		{
			//player->useRandomCostItemFromInventory();	//TODO: 랜덤 아이템 사용(pull)
		}

		int playerDamage = 10; /* player->getAttackDamage();*/	// TODO: 치명타 확률까지 계산한 최종 공격 데미지 반환하는 함수 제작
		newMonster->takeDamage(playerDamage);
		std::cout << player->getName() << "이/가 " << newMonster->getName() << "을/를 공격합니다! (데미지: " << playerDamage << ") ▶ ";
		if (newMonster->getHealth() <= 0)					// 몬스터 사망시
		{
			std::cout << newMonster->getName() << " 처치!\n";

			player->increaseExperience(50 /*WIN_EXP*/);		// 경험치, 골드 획득
			int randomGold = RandomUtil::getInt(10, 20/*WIN_GOLD_MIN, WIN_GOLD_MAX*/);
			player->increaseGold(randomGold);
			std::cout << "전투에서 승리했습니다! EXP(+50)와 골드(+" << randomGold << ")를 획득했습니다.";
			std::cout << " 현재 레벨 : " << player->getLevel() << "(" << player->getExperience() << "/100), 골드 : " << player->getGold() << "\n";
			
			if (RandomUtil::getInt(0, 99) < 30)				// 30% 확률로 아이템 드랍
			{
				/*player->addItemToInventory(newMonster->dropItem());*/		// TODO: unique_ptr이라 move 써야할수도?
			}
			break;
		}
		std::cout << newMonster->getName() << " 체력 : " << newMonster->getHealth() << "\n";

		int monsterDamage = newMonster->getAttack();
		int beforePlayerHP = player->getHealth();
		std::cout << newMonster->getName() << "이/가 " << player->getName() << "을/를 공격합니다! (데미지: " << monsterDamage << ") ▶ ";
		player->takeDamage(monsterDamage);				
		if (player->getHealth() <= 0)					
		{
			std::cout << player->getName() << " 체력 : " << beforePlayerHP << " → 0\n";
			break;
		}
		std::cout << player->getName() << " 체력 : " << beforePlayerHP << " → " << player->getHealth() << "\n";
	}
}

/* 사용자 입력받기(숫자만) */
int GameManager::getNumberFromUserInput(const std::string& prompt = "숫자를 입력해주세요: ")
{
	int choice;

	while (true)
	{
		std::cout << prompt;
		std::cin >> choice;
		if (cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "[ERR] 잘못된 입력입니다. 숫자만 입력하세요\n";
			continue;
		}
		cin.ignore();	// 개행문자 제거
		break;
	}
	return choice;
}

/* 플레이어가 상점을 방문했을 때의 행동 정의 */
void GameManager::visitShop()
{
	std::cout << "\n[상점에 방문했습니다]\n";
	while (true)
	{
		std::cout << "상점 메뉴:\n";
		std::cout << "1. 구매\n2.판매\n0. 나가기\n";
		int shopChoice = getNumberFromUserInput("상점메뉴를 선택해주세요: ");
		if(shopChoice == 0)	// 상점 나가기
		{
			std::cout << "상점을 나갑니다.\n";
			break;
		}
		else if (shopChoice == 1)	// 아이템 구매
		{
			shop->buy(Character::getInstance());	// TODO: Shop->buy() 함수 구현
		}
		else if (shopChoice == 2)	// 아이템 판매
		{
			shop->sell(Character::getInstance());	// TODO: Shop->sell() 함수 구현
		}
		else
		{
			std::cout << "잘못된 입력입니다. 다시 시도해주세요.\n\n";
		}

	}





	//// 0. 캐릭터 싱글톤 받아오기
	//Character* player = Character::getInstance();

	//// 1. 캐릭터 Inventory, Gold, stat 표시
	//player->displayStatus();
	//player->displayInventory();

	//// 2. 상점 목록 display
	////ItemManager itemManager = ItemManager::getInstance();
	////std::unique_ptr<Shop> shop = std::make_unique<Shop>();

	//while (true)
	//{
	//	printf("상점 메뉴를 선택해주세요.\n");
	//	printf("1. 아이템 구매\n");
	//	printf("2. 아이템 판매\n");
	//	printf("3. 상점 나가기\n");

	//	int menuChoice = getNumberFromUserInput();

	//	if (menuChoice == 1)
	//	{
	//		std::cout << "구매할 아이템을 선택해주세요(-1 : 뒤로가기) : ";
	//		//TODO: itemManager->display(무기,방어구,포션) 표시
	//		int itemIdx = getNumberFromUserInput();	// item idx를 선택하도록
	//		if (itemIdx == -1) {		// 뒤로가기
	//			continue;
	//		}
	//		//std::unique_ptr<IItem> newItem = itemManager->getItemList().at(itemIdx)->clone();
	//		//IItem* item = getItem(itemId); // TODO: 해당 아이템 정보 가져오기
	//		if (player->getGold() >= 0 /* item.price */)
	//		{
	//			//player->decreaseGold(newItem.getPrice);
	//			//player->addItemToInventory(std::move(newItem));
	//		}
	//	}
	//	else if (menuChoice == 2)
	//	{
	//		std::cout << "인벤토리에서 판매할 아이템을 선택해주세요 : ";
	//		//player->displayInventory();	// 위에서 보여줘서 안해도 될...듯?
	//		int itemId = getNumberFromUserInput();	// item id를 선택하도록
	//		if (itemId == -1) {		// 뒤로가기
	//			continue;
	//		}
	//		//IItem* item = getItem(itemId);	// TODO: 해당 아이템 정보 가져오기
	//		player->removeItemFromInventory(itemId);	// TODO: itemId로 삭제
	//		//player->increaseGold(item->getPrice * 0.6);	// 원가의 60%로 판매
	//	}
	//	else if (menuChoice == 3)
	//	{
	//		printf("상점을 종료합니다.\n");
	//		break;
	//	}
	//	else
	//	{
	//		std::cout << "1 ~ 3 사이의 숫자를 입력해주세요.\n";
	//	}
	//}
}