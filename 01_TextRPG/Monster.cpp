#include <iostream>
#include "Monster.h"
#include "RandomUtil.h"
#include "Item.h"
#include "Player.h"


Monster::Monster(const std::string& name, int level, int hp, int attack, bool isBoss)
	: name(name), level(level), maxHP(hp), curHP(hp), attack(attack), isBoss(isBoss){}

void Monster::takeDamage(int damage)
{
	curHP -= damage;
	if (curHP < 0) curHP = 0;
}

void Monster::attackPlayer(Player& player)
{
	std::cout << "[피격] " << name << "이(가) " << player.getName() << "을(를) 공격합니다! " << player.getName() << " 체력: " << player.getCurrentHP() << "\n";
	player.takeDamage(attack);
}

std::unique_ptr<Item> Monster::dropItem()
{
	std::cout << "[아이템 드랍] " << name << "으로부터 ";

	int probability = RandomUtil::getInt(1, 100);

	if (probability <= 25)	// TODO: Constants;
	{	// 25% 확률로 Attack Boost 포션을 드랍함
		std::cout << "힘의 영약을 획득했습니다\n";
		return std::move(std::make_unique<AttackBoost>());
	}
	else if (probability <= 50)			// TODO: Constants
	{	// 25% 확률로 치명타 증가 물약을 드랍함
		std::cout << "치명타 증가 물약을 획득했습니다\n";
		return std::move(std::make_unique<CriticalBoost>());
	}
	else if (probability <= 100)
	{
		// 50% 확률로 HP 포션을 드랍함
		std::cout << "HP 포션을 획득했습니다\n";
		return std::move(std::make_unique<HP_Potion>());
	}
}

bool Monster::isAlive() const
{
	return curHP > 0;
}

std::string Monster::getName() const
{
	return name;
}

int Monster::getHP() const
{
	return curHP;
}

int Monster::getLevel() const
{
	return level;
}

/* 몬스터 종류별 생성자 */
Goblin::Goblin(int playerLevel)				// TODO: Constants
	:Monster("고블린", playerLevel, playerLevel * RandomUtil::getInt(20, 30), playerLevel * RandomUtil::getInt(5, 10), false)
{
	std::cout << "몬스터 "<< name << " 등장! 체력: " << curHP << ", 공격력 : " << attack << "\n";	// TODO: 제안사항대로 출력
}

Orc::Orc(int playerLevel)					// TODO: Constants
	:Monster("오크", playerLevel, playerLevel* RandomUtil::getInt(20, 30), playerLevel* RandomUtil::getInt(5, 10), false) 
{
	std::cout << "몬스터 " << name << " 등장! 체력: " << curHP << ", 공격력 : " << attack << "\n";			// TODO: 제안사항대로 출력
}

Troll::Troll(int playerLevel)				// TODO: Constants
	:Monster("트롤", playerLevel, playerLevel* RandomUtil::getInt(20, 30), playerLevel* RandomUtil::getInt(5, 10), false) 
{
	std::cout << "몬스터 " << name << " 등장! 체력: " << curHP << ", 공격력 : " << attack << "\n";			// TODO: 제안사항대로 출력
}

BossMonster::BossMonster(int playerLevel)	// TODO: Constants
	:Monster("드래곤", playerLevel, playerLevel* RandomUtil::getInt(30, 45), playerLevel* RandomUtil::getInt(8, 15), true)
{
	std::cout << "보스 몬스터 " << name << " 등장! 체력: " << curHP << ", 공격력 : " << attack << "\n";			// TODO: 제안사항대로 출력
}
