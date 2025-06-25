#include <iostream>
#include <memory>
#include <algorithm>
#include "Player.h"
#include "Monster.h"
#include "RandomUtil.h"

std::unique_ptr<Player> Player::instance = nullptr;

Player::Player(const std::string& name)
	: name(name), level(Constants::DEFAULT_LEVEL), maxHP(Constants::DEFAULT_HP),
	curHP(Constants::DEFAULT_HP), attack(Constants::DEFAULT_ATK), 
	exp(Constants::DEFAULT_EXP), gold(Constants::DEFAULT_GOLD)		
{
	// std::cout << "[FOR DEBUG : Player.cpp > Player]\n";
}


Player& Player::getInstance(const std::string& name /*= "Hero"*/)
{
	// std::cout << "[FOR DEBUG : Player.cpp > getInstance]\n";
	if (!instance)
	{
		instance = std::unique_ptr<Player>(new Player(name));
	}
	return *instance;
}

void Player::showStatus() const
{
	// std::cout << "[FOR DEBUG : Player.cpp > ShowStatus]\n";

	std::cout << "\n-----------[플레이어 상태]------------\n";
	std::cout << "| 이름: \"" << name << "\"  |  골드: " << gold 
		<< "\n| 레벨: " << level << " (Exp: " << exp << "/100)  |  HP: "
		<< curHP << "/" << maxHP;
	std::cout << "\n| 공격력: " << attack << "(+" << tempAttackBuff << ")  |  치명타 확률: "
		<< criticalProbability << "(+" << tempCriticalProbability << ")\n| 인벤토리: ";
	if (inventory.empty()) 
		std::cout << "없음";
	else 
		for (auto& item : inventory) 
			std::cout << "[" << item->getName() << "] ";
	std::cout << "\n--------------------------------------\n\n";
}

void Player::resetTempAbility()
{
	// std::cout << "[FOR DEBUG : Player.cpp > resetTempAbility]\n";
	tempAttackBuff = 0;
	tempCriticalProbability = 0;
}

void Player::useItem()
{
	// std::cout << "[FOR DEBUG : Player.cpp > useItem]\n";
	if (!hasConsumable())
	{
		std::cout << "인벤토리에 사용 가능한 아이템이 없습니다.\n";
		return;
	}
	for (size_t i = 0; i < inventory.size(); ++i)
	{
		if (inventory[i]->isConsumable())
		{
			//std::cout << "[아이템 사용] " << inventory[i]->getName() << "\n";
			inventory[i]->use(*this);
			inventory.erase(inventory.begin() + i);
			break;
		}
	}
}

void Player::useItemUsingIndex(int index)
{
	bool isSuccess = inventory[index]->use(*this);
	if (isSuccess)
	{
		inventory.erase(inventory.begin() + index);
	}
}

void Player::attackMonster(Monster& monster)
{
	// std::cout << "[FOR DEBUG : Player.cpp > attackMonster]\n";
	int attackDamage = getAttackDamage();
	std::cout << "[공격] : \"" << name << "\"이(가) \"" << monster.getName() << "\"을(를) 공격합니다!(데미지: " << attackDamage << ") → \"" << monster.getName() << "\" 체력(" << monster.getCurHP();
	monster.takeDamage(attackDamage);
	std::cout << " → " << monster.getCurHP() << ") / " << monster.getMaxHP() << "\n";
}

void Player::takeDamage(int damage)
{
	// std::cout << "[FOR DEBUG : Player.cpp > takeDamage]\n";
	curHP -= damage;
	if (curHP < 0) curHP = 0;
}

void Player::addExp(int amount)
{
	// std::cout << "[FOR DEBUG : Player.cpp > addExp]\n";
	exp += amount;
	levelUp();
}

void Player::addGold(int amount)
{
	// std::cout << "[FOR DEBUG : Player.cpp > addGold]\n";
	gold += amount;
}

void Player::increaseAttack(int amount)
{
	if (amount<0) return;
	attack+=amount;
}

void Player::increaseCriticalProbability(int amount)
{
	if (amount<0) return;
	criticalProbability+=amount;
}

void Player::increaseCurrentHP(int amount)
{
	if (amount < 0)	return;
	curHP += amount;
	if (curHP > maxHP) curHP = maxHP;
}

void Player::increaseMaxHP(int amount)
{
	if (amount<0) return;
	maxHP+=amount;
}

void Player::decreaseAttack(int amount)
{
	if (amount<0) return;
	attack-=amount;
}

void Player::decreaseCriticalProbability(int amount)
{
	if (amount<0) return;
	criticalProbability-=amount;
}

void Player::decreaseMaxHP(int amount)
{
	if (amount<0) return;

	maxHP-=amount;
	
	if (curHP > maxHP)
	{curHP = maxHP;}
}

void Player::subtractGold(int amount)
{
	// std::cout << "[FOR DEBUG : Player.cpp > addGold]\n";
	gold -= amount;		// NOTE: gold가 음수가 될 수 있음. 호출부에서 잘 처리할 필요 있음
}

void Player::addItem(std::unique_ptr<Item> item)
{
	// std::cout << "[FOR DEBUG : Player.cpp > addItem]\n";
	inventory.push_back(std::move(item));
}

void Player::healHP(int amount)
{
	// std::cout << "[FOR DEBUG : Player.cpp > healHP]\n";
	std::cout << "HP가 +" << amount << " 회복되었습니다(체력: " << curHP;
	curHP += amount;
	if (curHP > maxHP)	curHP = maxHP;
	std::cout << " → " << curHP << " / " << maxHP << ")\n";
}

void Player::addTempAttack(int amount)
{
	// std::cout << "[FOR DEBUG : Player.cpp > addTempAttack]\n";
	std::cout << "공격력이 +" << amount << " 증가했습니다!(공격력: " << attack + tempAttackBuff;
	tempAttackBuff += amount;
	std::cout << " → " << attack + tempAttackBuff << ")\n";
}

void Player::addTempCriticalProbability(int amount)
{
	// std::cout << "[FOR DEBUG : Player.cpp > addTempCriticalProbability]\n";
	std::cout << "치명타 확률이 +" << amount << " 증가했습니다!(치명타 확률: " << criticalProbability + tempCriticalProbability;
	tempCriticalProbability += amount;
	std::cout << " → " << criticalProbability + tempCriticalProbability << ")\n";
}

void Player::removeItemByIdx(int idx)
{
	// std::cout << "[FOR DEBUG : Player.cpp > removeItemByIdx]\n";
	inventory.erase(inventory.begin() + idx);
}

void Player::displayInventory()
{
	// std::cout << "[FOR DEBUG : Player.cpp > displayInventory]\n";
	std::cout << "\n---------------[ 보유 아이템 목록 ]-----------------\n|\n";
	for (size_t i = 0; i < inventory.size(); ++i)
	{
		std::cout << "| " << i + 1 << ". " << inventory[i]->getName() << " : " << inventory[i]->getDescription() << "\n";
	}
	std::cout << "|\n----------------------------------------------------\n";
}

bool Player::isAlive() const 
{
	// std::cout << "[FOR DEBUG : Player.cpp > isAlive]\n";
	return curHP > 0;
}

bool Player::hasConsumable() const
{
	// std::cout << "[FOR DEBUG : Player.cpp > hasConsumable]\n";
	return std::any_of(inventory.begin(), inventory.end(), [](const std::unique_ptr<Item>& item) {
		return item->isConsumable(); 
	});
}

int Player::getLevel() const 
{
	// std::cout << "[FOR DEBUG : Player.cpp > getLevel]\n";
	return level;
}

int Player::getGold() const
{
	// std::cout << "[FOR DEBUG : Player.cpp > getGold]\n";
	return gold;
}

int Player::getExp() const
{
	// std::cout << "[FOR DEBUG : Player.cpp > getExp]\n";
	return exp;
}

std::string Player::getName() const
{
	// std::cout << "[FOR DEBUG : Player.cpp > getName]\n";
	return name;
}

int Player::getCurrentHP() const
{
	return curHP;
}

int Player::getMaxHP() const
{
	return maxHP;
}

std::vector<std::unique_ptr<Item>>& Player::getInventory()
{
	// std::cout << "[FOR DEBUG : Player.cpp > getInventory]\n";
	return inventory;
}

void Player::equipWeapon(std::unique_ptr<Item> weapon)
{
	unEquipWeapon();
	
	equippingWeapon = std::move(weapon);
	
	IWeapon* tempWeapon = dynamic_cast<IWeapon*>(equippingWeapon.get());
	if (tempWeapon)
	{
		tempWeapon->equipped(*this);				
	}
}

void Player::equipArmor(std::unique_ptr<Item> armor)
{
	unEquipArmor();
	
	equippingArmor = std::move(armor);
	
	IArmor* tempArmor = dynamic_cast<IArmor*>(equippingArmor.get());
	if (tempArmor)
	{
		tempArmor->equipped(*this);				
	}
}
void Player::unEquipWeapon()
{
	if (!equippingWeapon) return;

	IWeapon* tempWeapon = dynamic_cast<IWeapon*>(equippingWeapon.get());
	if (tempWeapon)
	{
		tempWeapon->unEquipped(*this);				
	}
	
	addItem(std::move(equippingWeapon));
	equippingWeapon = nullptr;
}



void Player::unEquipArmor()
{
	if (!equippingArmor) return;

	IArmor* tempArmor = dynamic_cast<IArmor*>(equippingArmor.get());
	if (tempArmor)
	{
		tempArmor->unEquipped(*this);				
	}
	
	addItem(std::move(equippingArmor));
	equippingArmor = nullptr;
}


/* 내부 호출용 함수 */
int Player::getAttackDamage() const
{
	// std::cout << "[FOR DEBUG : Player.cpp > getAttackDamage]\n";
	
	int damage = attack + tempAttackBuff;
	
	int randomInt = RandomUtil::getInt(1, 100);
	if (randomInt <= getCriticalProbability())
	{
		return (damage) * Constants::DEFAULT_CRITICAL_DAMAGE;
	}
	return (damage);
}

int Player::getCriticalProbability() const
{
	// std::cout << "[FOR DEBUG : Player.cpp > getCriticalProbability]\n";
	return criticalProbability + tempCriticalProbability;
}

void Player::levelUp()
{
	// std::cout << "[FOR DEBUG : Player.cpp > levelUp]\n";
	while (exp >= Constants::MAX_EXP && level < Constants::MAX_LEVEL)
	{
		exp -= Constants::MAX_EXP;
		++level;
		maxHP += Constants::LEVEL_HP_RATE;
		attack += Constants::LEVEL_ATK_RATE;

		curHP = maxHP;
		std::cout << "[레벨업] : " << level << "레벨(체력: " << maxHP << ", 공격력: " << attack << ")\n";
	}
}