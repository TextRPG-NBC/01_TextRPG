#include <iostream>
#include <algorithm>
#include "Player.h"
#include "Monster.h"
#include "RandomUtil.h"

std::unique_ptr<Player> Player::instance = nullptr;

Player::Player(const std::string& name)
	: name(name), level(1), maxHP(200), curHP(200), attack(30), exp(0), gold(0)		// TODO: Constants
{
	std::cout << "[FOR DEBUG : Player.cpp > Player]\n";
}


Player& Player::getInstance(const std::string& name /*= "Hero"*/)
{
	std::cout << "[FOR DEBUG : Player.cpp > getInstance]\n";
	if (!instance)
	{
		instance = std::unique_ptr<Player>(new Player(name));
		// 싱글톤의 private 생성자는 클래스 멤버에서만 new로 생성할 수 있고
		// make_unique는 외부 함수라서 private 생성자에 접근이 안됨
	}
	return *instance;
}

void Player::showStatus() const
{
	std::cout << "[FOR DEBUG : Player.cpp > ShowStatus]\n";

	std::cout << "\n====== [플레이어 상태] ======\n";
	std::cout << "이름: " << name
		<< " | 레벨: " << level << " (Exp: " << exp << "/100)\n";
	std::cout << "HP: " << curHP << "/" << maxHP
		<< " | 공격력: " << attack
		<< " | 골드: " << gold << "\n";
	std::cout << "인벤토리: ";
	if (inventory.empty()) std::cout << "없음";
	else for (auto& item : inventory) std::cout << "[" << item->getName() << "] ";
	std::cout << "\n============================\n";
}

void Player::resetTempAbility()
{
	std::cout << "[FOR DEBUG : Player.cpp > resetTempAbility]\n";
	tempAttackBuff = 0;
	tempCriticalProbability = 0;
}

void Player::useItem()
{
	std::cout << "[FOR DEBUG : Player.cpp > useItem]\n";
	if (!hasConsumable())
	{
		std::cout << "인벤토리에 사용 가능한 아이템이 없습니다.\n";
		return;
	}
	for (size_t i = 0; i < inventory.size(); ++i)
	{
		if (inventory[i]->isConsumable())
		{
			std::cout << "[아이템 사용] " << inventory[i]->getName() << "\n";
			inventory[i]->use(*this);
			inventory.erase(inventory.begin() + i);
			break;
		}
	}
}

void Player::attackMonster(Monster& monster)
{
	std::cout << "[FOR DEBUG : Player.cpp > attackMonster]\n";
	int attackDamage = getAttackDamage();
	monster.takeDamage(attackDamage);
	std::cout << name << " 공격, 데미지: " << attackDamage << "\n";
}

void Player::takeDamage(int damage)
{
	std::cout << "[FOR DEBUG : Player.cpp > takeDamage]\n";
	curHP -= damage;
	if (curHP < 0) curHP = 0;
	std::cout << name << "이 " << damage << "받았음. 남은 HP : " << curHP << "/" << maxHP <<"\n";		// TODO: 출력 포멧 수정
}

void Player::addExp(int amount)
{
	std::cout << "[FOR DEBUG : Player.cpp > addExp]\n";
	exp += amount;
	levelUp();
}

void Player::addGold(int amount)
{
	std::cout << "[FOR DEBUG : Player.cpp > addGold]\n";
	gold += amount;
}

void Player::subtractGold(int amount)
{
	std::cout << "[FOR DEBUG : Player.cpp > addGold]\n";
	gold -= amount;		// NOTE: gold가 음수가 될 수 있음. 호출부에서 잘 처리할 필요 있음
}

void Player::addItem(std::unique_ptr<Item> item)
{
	std::cout << "[FOR DEBUG : Player.cpp > addItem]\n";
	inventory.push_back(std::move(item));
}

void Player::healHP(int amount)
{
	std::cout << "[FOR DEBUG : Player.cpp > healHP]\n";
	curHP += amount;
	if (curHP > maxHP)	curHP = maxHP;
	std::cout << "HP가 +" << amount << " 회복되었습니다(체력: " << curHP << "/" << maxHP << ")\n";
}

void Player::addTempAttack(int amount)
{
	std::cout << "[FOR DEBUG : Player.cpp > addTempAttack]\n";
	tempAttackBuff += amount;
	std::cout << "이번 전투동안 공격력이 +" << amount << " 증가했습니다!(공격력: " << attack + tempAttackBuff << ")\n";
}

void Player::addTempCriticalProbability(int amount)
{
	std::cout << "[FOR DEBUG : Player.cpp > addTempCriticalProbability]\n";
	tempCriticalProbability += amount;
	std::cout << "이번 전투동안 치명타 확률이 +" << amount << " 증가했습니다!(치명타 확률: " << criticalProbability + tempCriticalProbability << ")\n";
}

void Player::removeItemByIdx(int idx)
{
	std::cout << "[FOR DEBUG : Player.cpp > removeItemByIdx]\n";
	inventory.erase(inventory.begin() + idx);
}

bool Player::isAlive() const 
{
	std::cout << "[FOR DEBUG : Player.cpp > isAlive]\n";
	return curHP > 0;
}

bool Player::hasConsumable() const
{
	std::cout << "[FOR DEBUG : Player.cpp > hasConsumable]\n";
	return std::any_of(inventory.begin(), inventory.end(), [](const std::unique_ptr<Item>& item) {
		return item->isConsumable(); 
	});
}

int Player::getLevel() const 
{
	std::cout << "[FOR DEBUG : Player.cpp > getLevel]\n";
	return level;
}

int Player::getGold() const
{
	std::cout << "[FOR DEBUG : Player.cpp > getGold]\n";
	return gold;
}

int Player::getExp() const
{
	std::cout << "[FOR DEBUG : Player.cpp > getExp]\n";
	return exp;
}

std::string Player::getName() const
{
	std::cout << "[FOR DEBUG : Player.cpp > getName]\n";
	return name;
}

std::vector<std::unique_ptr<Item>>& Player::getInventory()
{
	std::cout << "[FOR DEBUG : Player.cpp > getInventory]\n";
	return inventory;
}

/* 내부 호출용 함수 */
int Player::getAttackDamage() const
{
	std::cout << "[FOR DEBUG : Player.cpp > getAttackDamage]\n";
	int randomInt = RandomUtil::getInt(1, 100);
	if (randomInt <= getCriticalProbability())
	{
		return (attack + tempAttackBuff) * 2;	// TODO: Constants(치뎀으로 확장 가능)
	}
	return (attack + tempAttackBuff);
}

int Player::getCriticalProbability() const
{
	std::cout << "[FOR DEBUG : Player.cpp > getCriticalProbability]\n";
	return criticalProbability + tempCriticalProbability;
}

void Player::levelUp()
{
	std::cout << "[FOR DEBUG : Player.cpp > levelUp]\n";
	while (exp >= 100 && level < 10)	// TODO: Constants
	{
		exp -= 100;
		++level;
		maxHP += level * 20;		// TODO: Constants
		attack += level * 5;		// TODO: Constants
		curHP = maxHP;
		std::cout << "[레벨업] " << level << "레벨! 체력 : " << maxHP << " 공격력: " << attack << "\n";	// TODO: 출력포멧팅
	}
}