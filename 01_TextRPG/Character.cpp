#include "Character.h"
#include"IItem.h"
#include"Weapon.h"
#include"Armor.h"
#include <iostream>

std::unique_ptr<Character> Character::instance = nullptr;

// ================ 퍼블릭 함수 ================

Character* Character::getInstance()
{
	if(!instance)
	{
		instance.reset(new Character("레오니다스 1세", 1));
		// instance = std::make_unique<Character>("레오니다스 1세", 1);
		// 위와 같이 작성할 경우 생성자를 Private에 두었을 때 에러가 발생하는데 이유를 모르겠음.
		// 때문에 instance.reset() 을 사용함.
		
	}
	return instance.get();
}

std::string Character::getName() const
{
	return name;
}

int Character::getLevel() const
{
	return level;
}

int Character::getExperience() const
{
	return experience;
}

int Character::getHealth() const
{
	return health;
}

int Character::getMaxHealth() const
{
	return maxHealth;
}

int Character::getAttack() const
{
	return attack;
}

int Character::getCritical() const
{
	return criticalProbability;
}

bool Character::getIsDead() const
{
	return health <= 0;
}

int Character::getGold() const
{
	return gold;
}

Character* Character::displayStatus() const
{
	using namespace std;
	cout << "===== "<< name <<"의 정보 =====" << endl;
	cout << "레벨: " << level << endl;
	cout << "체력: " << health << "/" << maxHealth << endl;
	cout << "공격력: " << attack << endl;
	cout << "치명타 확률: " << criticalProbability << "%" << endl;
	cout << "경험치: " << experience << endl;
	cout << "소지금: " << gold << " 골드" << endl;

	return instance.get();
}

Character* Character::increaseExperience(int amount)
{
	if (level > 10) return instance.get();
	std::cout << name << "가 " << amount << " 경험치를 얻었습니다." << std::endl;
	experience += amount;
	if (experience >= 100)
	{
		levelUp();
	}
	std::cout << name << "의 현재 경험치: " << experience << std::endl;
	return instance.get();
}

Character* Character::recovery(int amount)
{
	std::cout << name << "가 " << amount << "만큼 회복했습니다." << std::endl;
	setHealth(health + amount);
	return instance.get();
}

Character* Character::recoveryToFullCondition()
{
	health = maxHealth;
	return instance.get();
}

Character* Character::attackToMonster(IMonster* target)
{
	std::cout << "Character.cpp 의 attackToMonster함수: 몬스터가 인클루드 되지 않았습니다." << std::endl;
	std::cout << "Character.cpp 의 attackToMonster함수: 이 함수는 구현되지 않았습니다." << std::endl;
	return instance.get();
}

Character* Character::takeDamage(int amount)
{
	std::cout << name << "가 " << amount << "만큼 피해를 입었습니다." << std::endl;
	setHealth(health - amount);
	return instance.get();
}

Character* Character::increaseAttackBoost(int amount)
{
	std::cout << name << "의 공격력이 " << amount << "만큼 증가했습니다." << std::endl;
	attackBoostAmount += amount;
	calculateStat();
	return instance.get();
}

Character* Character::decreaseAttackBoost(int amount)
{
	std::cout << name << "의 공격력이 " << amount << "만큼 감소했습니다." << std::endl;
	attackBoostAmount -= amount;
	calculateStat();
	return instance.get();
}

Character* Character::increaseCriticalBoost(int increasePercent)
{
	std::cout << name << "의 치명타 확률이 " << increasePercent << "% 증가했습니다." << std::endl;
	criticalBoostAmount += increasePercent;
	calculateStat();
	return instance.get();
}

Character* Character::decreaseCriticalBoost(int decreasePercent)
{
	std::cout << name << "의 치명타 확률이 " << decreasePercent << "% 감소했습니다." << std::endl;
	criticalBoostAmount -= decreasePercent;
	calculateStat();
	return instance.get();
}

Character* Character::increaseMaxHealthBoost(int amount)
{
	std::cout << name << "의 최대 체력이 " << amount << "만큼 증가했습니다." << std::endl;
	maxHealthBoostAmount += amount;
	return instance.get();
}

Character* Character::decreaseMaxHealthBoost(int amount)
{
	std::cout << name << "의 최대 체력이 " << amount << "만큼 감소했습니다." << std::endl;
	maxHealthBoostAmount -= amount;
	return instance.get();
}

Character* Character::increaseGold(int amount)
{
	std::cout << name << "가 " << amount << " 골드를 얻었습니다." << std::endl;
	setGold(gold + amount);
	return instance.get();
}

// 포인터에 바로 사용할 수 없어서 삭제 대기. *(Character::getinstance()) << 처럼 사용하면 사용할 수 있지만 번거러움.
//Character* Character::operator<<(int gold)
//{
//	return increaseGold(gold);
//}

Character* Character::decreaseGold(int amount)
{
	std::cout << name << "의 " << amount << " 골드가 줄었습니다." << std::endl;
	setGold(gold - amount);
	return instance.get();
}

Character* Character::displayInventory() const
{
	if(inventory.empty())
	{
		std::cout << "인벤토리가 비어 있습니다." << std::endl;
		return instance.get();;
	}

	std::cout << "===== " << name << "의 인벤토리 =====" << std::endl;
	int index = 0;
	for(const auto& item : inventory)
	{
		std::cout << index << " : " << item->getName() << std::endl;
		index++;
	}
	return instance.get();
}

Character* Character::useItemFromInventory(int index)
{
	using namespace std;
	if (index < 0 || index >= inventory.size())
	{
		std::cout << "유효하지 않은 인덱스 입니다. 아이템을 사용하지 못했습니다." << std::endl;
		return instance.get();
	}
	
	inventory.at(index)->use(this);
	removeItemFromInventory(index);
	return instance.get();
}

int Character::getInventoryLength()
{
	return static_cast<int>(inventory.size());
}

Character* Character::removeItemFromInventory(int index)
{
	if (index < 0 || index >= inventory.size())
	{
		std::cout << "유효하지 않은 인덱스 입니다. 아이템을 지우지 못했습니다." << std::endl;
		return instance.get();
	}
	std::cout << inventory[index]->getName() << "이(가) 인벤토리에서 사라졌습니다." << std::endl;
	inventory.erase(inventory.begin() + index);
	return instance.get();
}

Character* Character::addItemToInventory(std::unique_ptr<IItem> item)
{
	inventory.push_back(std::move(item));
	std::cout << inventory.back()->getName() << "이(가) 인벤토리에 추가되었습니다." << std::endl;
	return instance.get();
}

// 포인터에 바로 사용할 수 없어서 삭제 대기. *(Character::getinstance()) << 처럼 사용하면 사용할 수 있지만 번거러움.
//Character* Character::operator<<(std::unique_ptr<IItem> item)
//{
//	return addItemToInventory(std::move(item));
//}

Character* Character::equipWeapon(std::unique_ptr<Weapon> weapon)
{
    if (!weapon)
    {
        std::cout << "유효하지 않은 무기입니다." << std::endl;
		return instance.get();
    }

	unEquipWeapon();
	equipedWeapon = std::move(weapon);
	std::cout << name << "가 " << equipedWeapon->getName() << "을(를) 장착했습니다." << std::endl;
	calculateStat();
	std::cout << name << "의 공격력이 " << equipedWeapon->getAtttackBonus() << " 증가했습니다." << std::endl;
	std::cout << name << "의 치명타율이 " << equipedWeapon->getCriticalBonus() << " 증가했습니다." << std::endl;

	return instance.get();
}

Character* Character::unEquipWeapon()
{
	if (equipedWeapon)
	{
		std::cout << name << "가 " << equipedWeapon->getName() << "을(를) 탈착했습니다." << std::endl;

		std::cout << name << "의 공격력이 " << equipedWeapon->getAtttackBonus() << " 감소했습니다." << std::endl;
		std::cout << name << "의 치명타율이 " << equipedWeapon->getCriticalBonus() << " 감소했습니다." << std::endl;

		addItemToInventory(std::move(equipedWeapon));
		calculateStat();

		return instance.get();
	}
	else
	{
		return instance.get();
	}

	
}

Character* Character::equipArmor(std::unique_ptr<Armor> armor)
{
	if (!armor)
	{
		std::cout << "유효하지 않은 갑옷입니다." << std::endl;
		
		return instance.get();
	}

	unEquipArmor();

	equipedArmor = std::move(armor);
	std::cout << name << "가 " << equipedArmor->getName() << "을(를) 장착했습니다." << std::endl;
	calculateStat();
	std::cout << name << "의 최대체력이 " << equipedArmor->getMaxHealthBonus() << " 증가했습니다." << std::endl;
	
	return instance.get();
}

Character* Character::unEquipArmor()
{
	if (equipedArmor)
	{
		std::cout << name << "가 " << equipedArmor->getName() << "을(를) 탈착했습니다." << std::endl;
		std::cout << name << "의 최대체력이 " << equipedArmor->getMaxHealthBonus() << " 감소했습니다." << std::endl;
		addItemToInventory(std::move(equipedArmor));
		calculateStat();
		return instance.get();
	}
	else
	{
		return instance.get();
	}


}

// ================ 프라이빗 함수 ( 싱글톤을 위해 숨겨진 생성자 및 헬퍼 함수) ================

Character::Character(const std::string& name, int level)
	:name(name), level(level), experience(0), gold(0), equipedWeapon(nullptr), equipedArmor(nullptr),
	attackBoostAmount(0),criticalBoostAmount(0),maxHealthBoostAmount(0)
{
	calculateStat();
	recoveryToFullCondition();
}

void Character::levelUp()
{
	level++;
	experience -= 100;
	calculateStat();
	recoveryToFullCondition();
	std::cout << "레벨이 상승햇습니다." << std::endl;
	std::cout << "현재 레벨: " << level << std::endl;
	if (experience >= 100)
	{
		levelUp();
	}
}

void Character::calculateStat()
{
	// 레벨에 의한 설정
	maxHealth = 200 + (level - 1) * 20;
	attack = 30 + (level - 1) * 5;
	criticalProbability = 0;
	
	// 장비에 의한 설정.
	if (equipedWeapon)
	{
		attack += equipedWeapon->getAtttackBonus();
		criticalProbability += equipedWeapon->getCriticalBonus();
	}
	if (equipedArmor)
	{
		maxHealth += equipedArmor->getMaxHealthBonus();
	}

	// 부스트에 의한 설정.
	attack += attackBoostAmount;
	criticalProbability += criticalBoostAmount;
	maxHealth += maxHealthBoostAmount;

	if (maxHealth <= 0) maxHealth = 1;
	if (maxHealth < health) health = maxHealth;
	if (attack < 0) attack = 0;
	if (criticalProbability < 0) criticalProbability = 0;
	if (criticalProbability > 100) criticalProbability = 100;
}

void Character::setHealth(int value)
{
	health = value;
	if (health <= 0)
	{
		health = 0;
		std::cout << name << "의 현재 체력: " << '(' << health <<  '/' << maxHealth << ')' << std::endl;
		std::cout << name << "가 전사했습니다." << std::endl;
		return;
	}
	
	if (health >= maxHealth)
	{
		health = maxHealth;
	}
	
	std::cout << name << "의 현재 체력: " << '(' << health <<  '/' << maxHealth << ')' << std::endl;
}

void Character::setGold(int value)
{
	gold = value;
	if (gold < 0)
	{
		gold = 0;
	}
	std::cout << name << "의 현재 소지금: " << gold << " 골드" << std::endl;
}




