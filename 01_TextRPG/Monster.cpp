#include <iostream>
#include "Monster.h"
#include "RandomUtil.h"
#include "Item.h"
#include "Player.h"


Monster::Monster(const std::string& name, int level, int hp, int attack, bool isBoss)
	: name(name), level(level), maxHP(hp), curHP(hp), attack(attack), isBoss(isBoss){}

void Monster::takeDamage(int damage)
{
	std::cout << "[FOR DEBUG : Monster.cpp > takeDamage]\n";
	curHP -= damage;
	if (curHP < 0) curHP = 0;
	std::cout << "[" << name << "] 이(가) " << damage << " 데미지 받음! (HP: " << curHP << "/" << maxHP << ")\n";		// TODO: 제안사항대로 출력
}

void Monster::attackPlayer(Player& player)
{
	std::cout << "[FOR DEBUG : Monster.cpp > attackPlayer]\n";
	std::cout << name << " attack to " << player.getName() << " (데미지 : " << attack << ")\n";	// TODO: 제안사항대로 출력
	player.takeDamage(attack);
}

std::unique_ptr<Item> Monster::dropItem()
{
	std::cout << "[FOR DEBUG : Monster.cpp > dropItem]\n";
	std::cout << "[아이템 드랍] " << name << "으로부터 ";

	int probability = RandomUtil::getInt(1, 100);
	if (probability <= 50)			// TODO: Constants
	{	// 50% 확률로 HP 포션을 드랍함
		std::cout << "HP 포션을 획득했습니다\n";
		return std::move(std::make_unique<HP_Potion>());
	}
	else if (probability <= 100)	// TODO: Constants;
	{	// 50% 확률로 Attack Boost 포션을 드랍함
		std::cout << "힘의 영약을 획득했습니다\n";
		return std::move(std::make_unique<AttackBoost>());
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
	std::cout << "[FOR DEBUG : Monster.cpp > Goblin]\n";
	std::cout << "고블린 생성됨. 스텟, 기타 정보 표시 필요\n";			// TODO: 제안사항대로 출력
}

Orc::Orc(int playerLevel)					// TODO: Constants
	:Monster("오크", playerLevel, playerLevel* RandomUtil::getInt(20, 30), playerLevel* RandomUtil::getInt(5, 10), false) 
{
	std::cout << "[FOR DEBUG : Monster.cpp > Orc]\n";
	std::cout << "오크 생성됨. 스텟, 기타 정보 표시 필요\n";			// TODO: 제안사항대로 출력
}

Troll::Troll(int playerLevel)				// TODO: Constants
	:Monster("트롤", playerLevel, playerLevel* RandomUtil::getInt(20, 30), playerLevel* RandomUtil::getInt(5, 10), false) 
{
	std::cout << "[FOR DEBUG : Monster.cpp > Troll]\n";
	std::cout << "트롤 생성됨. 스텟, 기타 정보 표시 필요\n";			// TODO: 제안사항대로 출력
}

BossMonster::BossMonster(int playerLevel)	// TODO: Constants
	:Monster("보스몬스터", playerLevel, playerLevel* RandomUtil::getInt(30, 45), playerLevel* RandomUtil::getInt(8, 15), true)
{
	std::cout << "[FOR DEBUG : Monster.cpp > BossMonster]\n";
	std::cout << "보스 생성됨. 스텟, 기타 정보 표시 필요\n";			// TODO: 제안사항대로 출력
}
