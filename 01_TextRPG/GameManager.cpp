#include "GameManager.h"
// TODO: #include "Monster.h"
// TODO : #include "BossMonster.h"
// TODO : #include "Character.h"
#include <random>

/* 랜덤 일반 몬스터 생성 후 반환 */
Monster* GameManager::generateMonster(int level)
{
	int choice = dist(rng);
	switch (static_cast<MonsterType>(choice))
	{
		case MONSTER_TYPE_GOBLIN:
			return new Goblin(level);
		case MONSTER_TYPE_ORC:
			return new Orc(level);
		case MONSTER_TYPE_TROLL:
			return new Troll(level);
		default:
			return new Goblin(level); // 기본값으로 고블린 반환
	}
}

/* 보스 몬스터 생성 후 반환 */
BossMonster* GameManager::generateBossMonster(int level)
{

}

/* 몬스터 VS 플레이어 전투시작 */
void GameManager::battle(Character* player)
{

}

/* 플레이어가 상점을 방문했을 때의 행동 정의 */
void GameManager::visitShop(Character* player)
{

}

/* 플레이어 인벤토리 표시 */
void GameManager::displayInventory(Character* player)
{

}
