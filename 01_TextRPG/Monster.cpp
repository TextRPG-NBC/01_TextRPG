#include <iostream>
#include "Monster.h"
#include "RandomUtil.h"
#include "Item.h"
#include "Player.h"
#include "Equipments.h"


Monster::Monster(const std::string& name, int level, bool isBoss)
	: name(name), level(level), isBoss(isBoss){
	maxHP = level * RandomUtil::getInt(Constants::NM_MIN_HP_RATE, Constants::NM_MAX_HP_RATE);
	curHP = maxHP;
	attack = level * RandomUtil::getInt(Constants::NM_MIN_ATK_RATE, Constants::NM_MIN_ATK_RATE);
	if (isBoss)
	{
		maxHP *= Constants::BOSS_STATUS_RATE;
		curHP = maxHP;
		attack *= Constants::BOSS_STATUS_RATE;
		std::cout << "[보스 몬스터 생성] : \"";
	}
	else 
	{
		std::cout << "[일반 몬스터 생성] : \"";
	}
	std::cout << "\"" << name << "\" 등장!(체력: " << curHP << ", 공격력 : " << attack << ")\n";
}

void Monster::takeDamage(int damage)
{
	curHP -= damage;
	if (curHP < 0) curHP = 0;
}

void Monster::attackPlayer(Player& player)
{
	std::cout << "[피격] : \"" << name << "\"이(가) \"" << player.getName() << "\"을(를) 공격합니다!(데미지: " << attack << ") → "
		<< player.getName() << " 체력(" << player.getCurrentHP();
	player.takeDamage(attack);
	std::cout << " → " << player.getCurrentHP() << ") / " << player.getMaxHP() << "\n";
}

std::unique_ptr<Item> Monster::dropItem()
{
	std::cout << "[아이템 드랍] : " << name << "(으)로부터 ";

	int probability = RandomUtil::getInt(1, 100);

	if (probability <= 10)
	{
		// 10% 확률로 HP 포션을 드랍함
		std::cout << "나뭇가지를 획득했습니다\n";
		return std::move(std::make_unique<TreeBranch>());
	}
	else if (probability <= 20)
	{
		// 10% 확률로 HP 포션을 드랍함
		std::cout << "가죽갑옷을 획득했습니다\n";
		return std::move(std::make_unique<LeatherArmor>());
	}
	else if (probability <= 40)	
	{	// 20% 확률로 Attack Boost 포션을 드랍함
		std::cout << "힘의 영약을 획득했습니다\n";
		return std::move(std::make_unique<AttackBoost>());
	}
	else if (probability <= 60)			
	{	// 20% 확률로 치명타 증가 물약을 드랍함
		std::cout << "치명타 증가 물약을 획득했습니다\n";
		return std::move(std::make_unique<CriticalBoost>());
	}
	else if (probability <= 100)
	{
		// 40% 확률로 HP 포션을 드랍함
		std::cout << "HP 포션을 획득했습니다\n";
		return std::move(std::make_unique<HP_Potion>());
	}
	return nullptr;		//코드가 여기까지 오지 않지만 경고 방지용으로 추가
}

bool Monster::isAlive() const
{
	return curHP > 0;
}

std::string Monster::getName() const
{
	return name;
}

int Monster::getCurHP() const
{
	return curHP;
}

int Monster::getMaxHP() const
{
	return maxHP;
}

int Monster::getLevel() const
{
	return level;
}

/* 몬스터 종류별 생성자 */
Goblin::Goblin(int playerLevel) : Monster("고블린", playerLevel, false) {}

Orc::Orc(int playerLevel) : Monster("오크", playerLevel, false) {}

Troll::Troll(int playerLevel) : Monster("트롤", playerLevel, false) {}

BossMonster::BossMonster(int playerLevel) : Monster("드래곤", playerLevel, true) {}
