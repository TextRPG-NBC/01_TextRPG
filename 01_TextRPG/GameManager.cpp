#include "GameManager.h"
// TODO: #include "Monster.h"
// TODO : #include "Character.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <string>


/* 랜덤 일반 몬스터 생성 후 반환 */
Monster* GameManager::generateMonster(int level)
{
	int choice = monsterDist(rng);
	Monster* monster = nullptr;
	switch (static_cast<MonsterType>(choice))
	{
		case MONSTER_TYPE_GOBLIN:
			monster = new Goblin(level);
		case MONSTER_TYPE_ORC:
			monster = new Orc(level);
		case MONSTER_TYPE_TROLL:
			monster = new Troll(level);
		default:
			monster new Goblin(level); // 기본값으로 고블린 반환
	}

	if (monster == nullptr)	// Trouble shooting
	{
		std::cerr << "몬스터 생성 실패" << std::endl;
		return nullptr;
	}

	printf("몬스터 %s 생성! (체력 : %d, 공격력 : %d)\n",
		monster->getName().c_str(), monster->getHealth(), monster->getAttack());

	return monster;
}

/* 보스 몬스터 생성 후 반환 */
BossMonster* GameManager::generateBossMonster(int level)
{
	return new BossMonster(level);
}

Item* GameManager::dropRandomItem()
{
	// TODO : 아이템 드랍 로직 구현
	Item* item == nullptr;
	int itemChoice = itemDist(rng);
	switch (static_cast<ItemType>(itemChoice))
	{
		case ITEM_TYPE_HealthPotion:
			item = new HealthPotion();
			break;
		case ITEM_TYPE_AttackBoost:
			item = new AttackBoost();
			break;
		case ITEM_TYPE_CriticalBoost:
			item = new CriticalBoost();
			break;
	}
	return item;
}

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

		if (answer == "y" || answer == "yes") {
			return 'Y';
		}
		else if (answer == "n" || answer == "no")
		{
			return 'N';
		}
		else 
		{
			std::cout << "잘못된 입력입니다. Y 또는 N만 입력해주세요." << std::endl;
		}
	}
}

/* 몬스터 VS 플레이어 전투시작 */
void GameManager::battle(Character* player)
{
	printf("[전투를 시작합니다]\n");
	
	// 플레이어 레벨에 기반한 랜덤한 몬스터 생성
	Monster* monster = generateMonster(player->level);	

	// Player 혹은 Monster가 죽을 때까지 전투 진행
	while (player->health > 0 && monster->getHealth() > 0)
	{
	// 랜덤 아이템 사용
		if(basicDist(rng) < 20)	// 20% 확률로 아이템 사용
		{
			if (!player->inventory.empty())
			{
				int itemIndex = baicDist(rng) % player->inventory.size();
				Item* item = player->inventory[itemIndex];
				item->use(player);
				player->inventory.erase(player->inventory.begin() + itemIndex);
				printf("%s이/가 %s을/를 사용했습니다!\n", player->name.c_str(), item->getName().c_str());
			}
		}

	// 플레이어 공격
		int playerDamage = player->attack;	// TODO : 플레이어 데미지 반환 함수(치명타 적용)

		monster->takeDamage(playerDamage);	// 몬스터에게 데미지 적용
		printf("%s이/가 %s을/를 공격합니다!(데미지 : %d) ▶ ", player->name.c_str(), monster->getName().c_str(), playerDamage);

		if (monster->getHealth() <= 0)		// 몬스터가 죽었다면
		{
			int earnExp = 50;				// 플레이어 경험치(50)
			int earnGold = goldDist(rng);	// 골드(10~20) 획득
			player->exprience += earnExp;	
			player->gold += earnGold;

			if (player->exprience >= 100)	// 만약 레벨업 경험치를 초과했다면, 레벨업 처리
			{
				player->levelUp();
				player->exprience -= 100;
			}

			if(basicDist(rng) < 30)			// 30% 확률로 아이템 드랍
			{
				Item* droppedItem = dropRandomItem();			// 아이템 드랍
				player->inventory.emplace_back(droppedItem);	// 인벤토리에 추가

				printf("%s이/가 %s아이템을 드랍했습니다!\n", monster->getName().c_str(), droppedItem->getName());
			}

			printf("%s 처치!\n");
			printf("%s이/가 %d EXP와 %d골드를 획득했습니다. 현재 레벨 : Level %d (EXP : %d / 100), 골드 : %d\n",
				player->name.c_str(), player->level, earnExp, earnGold);
			break; // 몬스터가 죽으면 전투 종료
		}

	// 몬스터 공격
		int monsterDamage = monster->getAttack();

		printf("%s이/가 %s을/를 공격합니다!(데미지 : %d) ▶ ",
			monster->getName().c_str(), player->name.c_str(), monsterDamage);

		if(player->health - monsterDamage <= 0)	// 플레이어가 죽었다면
		{
			printf("%s 체력 : %d → 0\n", player->name.c_str(), player->health);
			printf("%s이/가 사망했습니다. 게임 오버!\n", player->name.c_str());
			exit(0);							// 게임 종료
		}

		player->health -= monsterDamage;		// 플레이어에게 데미지 적용
		printf("%s 체력 : %d\n", player->name.c_str(), player->health);
	}

	// 상점 방문
	char choice = inputYorN("전투가 종료되었습니다. 상점을 방문하시겠습니까? (Y/N) : ");
	if (choice == 'Y')
	{
		visitShop(player);
	}

	// TODO: delete() 혹은 smart pointer를 사용하여 몬스터 메모리 해제
}

/* 플레이어가 상점을 방문했을 때의 행동 정의 */
void GameManager::visitShop(Character* player)
{
	// TODO: 인벤토리 표시
	// TODO: 상점 아이템목록 표시
	// TODO: 아이템 구매(골드로 구매, 구매즉시 인벤토리에 추가)
	// TODO: 아이템 판매(보유한 아이템을 골드로 판매(구입 원가의 60%가격), 판매된 아이템은 인벤토리에서 제거)
}

/* 플레이어 인벤토리 표시 */
void GameManager::displayInventory(Character* player)
{
	// TODO : CLI 인벤토리 표시
}
