#include "GameManager.h"
// TODO: #include "Monster.h"
// TODO : #include "BossMonster.h"
// TODO : #include "Character.h"
#include <random>

/* ���� �Ϲ� ���� ���� �� ��ȯ */
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
			return new Goblin(level); // �⺻������ ��� ��ȯ
	}
}

/* ���� ���� ���� �� ��ȯ */
BossMonster* GameManager::generateBossMonster(int level)
{

}

/* ���� VS �÷��̾� �������� */
void GameManager::battle(Character* player)
{

}

/* �÷��̾ ������ �湮���� ���� �ൿ ���� */
void GameManager::visitShop(Character* player)
{

}

/* �÷��̾� �κ��丮 ǥ�� */
void GameManager::displayInventory(Character* player)
{

}
