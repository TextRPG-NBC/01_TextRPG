#include "GameManager.h"
#include "Constants.h"
#include "RandomUtil.h"
// TODO: #include "Monster.h"
// TODO : #include "Character.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>

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
	// TODO: 몬스터 생성정보 print는 Monster 생성자쪽에서 구현하는게 좋을 듯?
}

/* 보스 몬스터 생성, 반환(unique_ptr) */
std::unique_ptr<Monster> GameManager::generateBossMonster(int level)
{
	return std::make_unique<BossMonster>(level);
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
	// 1. print: 전투를 시작합니다.
	printf("[전투를 시작합니다]\n");

	// 2. 사전작업
	//	- 플레이어 싱글톤 받아오기 : 싱글톤을 unique_ptr로 만들면 다른데서 호출이 안되는데 특별한 이유가 있는지?
	//                             getInstance 아직 구현 안하신듯?
	//	- 플레이어 레벨기반 랜덤 몬스터 생성 (플레이어 레벨이 10 이상이면 보스몬스터, 아니면 일반몬스터)
	Character* myPlayer = Character::getInstance();
	std::unique_ptr<Monster> newMonster;
	if (myPlayer->getLevel() < 10 /*MAX_LEVEL*/)
	{
		newMonster = generateMonster(myPlayer->getLevel());
	}
	else 
	{
		newMonster = generateBossMonster(myPlayer->getLevel());
	}

	// 3. 전투반복(플레이어 or 몬스터가 살아있다면)
	//		플레이어 랜덤 아이템 사용(20% 확률), 아이템이 없으면 생략
	//		3.1 플레이어 공격턴 : 몬스터에게 데미지 적용(캐릭터: 치명타 포함 최종 공격값 반환)
	//			print : "플레이어"이/가 "몬스터"을/를 공격합니다! (데미지 ??) ▶ 
	//			3.1.1 몬스터가 죽었다면 
	//				print : "몬스터" 처치!\n
	//				플레이어 경험치 획득(+50), 골드(10~20) 획득 (레벨업은 Character에서 알아서 처리)
	//				아이템 획득(30%) (monster > drop Item 호출, Character의 Inventory에 추가)
	//				print : 전투에서 승리했습니다! ? EXP와 ? 골드를 획득했습니다. 현재 레벨?(?/100), 골드 ?
	//				전투종료(break)
	//			3.1.2 몬스터가 죽지 않았다면
	//				print : "몬스터" 체력 : ??\n
	//		3.2 몬스터 공격 턴 : 플레이어에게 데미지 적용(몬스터 공격력 적용)
	//			print : "몬스터"이/가 "플레이어"을/를 공격합니다! (데미지 ??) ▶ 
	//			3.2.1 플레이어가 죽었다면
	//				print : "플레이어" 체력 ?? -> 0\n
	//				print : "플레이어"이/가 사망했습니다. 게임오버\n!
	//				Character.isDead = true (Q. setIsDead 하나 만드셔야할듯? 아니 그냥 public에 있는데 쓰면되나?)
	//				break (여기서 바로 게임 끝내지 말고, main에서 플레이어 죽었다고 판단하면 따로 처리하는게 나을듯)
	//			3.2.2 플레이어가 죽지 않았다면
	//				print : "플레이어" 체력 : ??\n
	while (!myPlayer->getIsDead() && newMonster->getHealth() > 0)
	{
		if (myPlayer->getInventoryLength() > 0 && RandomUtil::getInt(0, 99) < 20)
		{
			myPlayer->useItemFromInventory(RandomUtil::getInt(0, myPlayer->getInventoryLength() - 1));
		}

		int playerDamage = player->getAttackDamage();	// TODO : 치명타 확률까지 계산한 최종 공격 데미지 반환하는 함수 제작
		newMonster->takeDamage(playerDamage);
		printf("%s 이/가 %s 을/를 공격합니다! (데미지 %d) ▶ ", myPlayer->getName().c_str(), newMonster->getName().c_str, playerDamage);
		if (newMonster->getHealth() <= 0)				// monster쪽에서 0 이하로 체력 깎이는거 방지해서 == 0으로 해도 무방
		{
			printf("%s 처치!\n", newMonster->getName().c_str());
			myPlayer->increaseExperience(50 /*WIN_EXP*/);
			int randomGold = myPlayer->increaseGold(RandomUtil::getInt(10, 20/*WIN_GOLD_MIN, WIN_GOLD_MAX*/));
			printf("전투에서 승리했습니다! EXP(+%d)와 골드(+%d)를 획득했습니다.", 50/*WIN_EXP*/, randomGold);
			printf("현재 레벨 : %d(%d/100), 골드 : %d\n", myPlayer->getLevel(), myPlayer->getExperience(), myPlayer->getGold());
			if (RandomUtil::getInt(0, 99) < 30)
			{
				myPlayer->AddItemToInventory(newMonster->dropItem());	// TODO : dropItem으로 *Item 반환, AddItemToInventory는 void로 해도 될거같은데
			}
			break;
		}
		printf("%s 체력 : %d\n", newMonster->getName().c_str(), newMonster->getHealth());

		int monsterDamage = newMonster->getAttack();	// 몬스터도 플레이어랑 통일성을 가지려면 치명타 넣고, 최종 공격력을 getAttackDamage로 반환하는 것. 그러나 이건 우선순위 밀림 생략
		int beforePlayerHP = myPlayer->getHealth();
		printf("%s 이/가 %s 을/를 공격합니다! (데미지 %d) ▶ ", newMonster->getName().c_str(), myPlayer->getName().c_str(), monsterDamage);
		myPlayer->takeDamage(monsterDamage);			// TODO: Character쪽에서 print 안하는게 수정하기 용이할듯?
		if (myPlayer->getHealth() <= 0)					// 0 이하로 안까이게 해놔서 == 0 해도 무방
		{
			printf("%s 체력 : %d → 0\n", myPlayer->getName().c_str(), beforePlayerHP);
			printf("%s 이/가 사망했습니다. 게임오버!\n", myPlayer->getName().c_str());
			myPlayer->isDead = true;	// TODO: setIsDead 함수 추가해서 상태 바꾸기
			break;
		}
		printf("%s 체력 : %d\n", myPlayer->getName().c_str(), myPlayer->getHealth());
	}
		
	// 4. 상점방문
	//		입력받기 : 상점을 방문하시겠습니까?(Y/N)
	//		4.1 Y
	//			상점방문
	char choice = inputYorN("전투가 종료되었습니다. 상점을 방문하시겠습니까? (Y/N) : ");
	if (choice == 'Y')
	{
		visitShop(player);
	}

	// 5. 메모리 해제(플레이어는 싱글톤이니 따로 할 필요없고, 몬스터만 해제하면 될 듯, 아니면 unique_ptr쓰던지)
	// delete newMonster; unique_ptr 써서 따로 안해도 될듯
}

/* 플레이어가 상점을 방문했을 때의 행동 정의 */
void GameManager::visitShop(Character* player)
{
	// 1. 캐릭터 Inventory, Gold, stat 표시
	// 2. 상점 목록 display
	// 3. 아이템 구매 (골드 차감, 인벤토리 추가)
	// 4. 아이템 판매 (골드 증가, 인벤토리 삭제)
	
	// TODO: 인벤토리 표시
	// TODO: 상점 아이템목록 표시
	// TODO: 아이템 구매(골드로 구매, 구매즉시 인벤토리에 추가)
	// TODO: 아이템 판매(보유한 아이템을 골드로 판매(구입 원가의 60%가격), 판매된 아이템은 인벤토리에서 제거)
}

/* 플레이어 인벤토리 표시 : 이거 필요없는거같은데? character에 붙이기 */
void GameManager::displayInventory(Character* player)
{
}
