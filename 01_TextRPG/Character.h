
// *** 캐릭터 사용안내 ***

// 캐릭터 클래스는 싱글톤으로 구현되었기 때문에 따로 인스턴스를 만들 수 없음.
// Character::getInstance()->함수이름() 과 같이 사용.
// 또는 #include "SCharacter.h" 이후 sc()->함수이름() 과 같이 사용.

// 전투)
// sc()->attackToMonster(goblin);
// goblin측의 공격함수에서 sc()->takeDamage(고블린의 공격력);
 
// 인벤토리에 아이템 추가)
// auto smallHealthPotion = makeHealthPotion("소형 생명력 물약", 20, 5); 
// auto 를 사용하지 않는 경우 std::unique_ptr<HealthPotion> 으로 받아야함.
// sc()->addItemToInventory(std::move(smallHealthPotion));
// sc()->addItemToInventory(makeHealthPotion("대형 생명력 물약", 50, 10)); // 임시객체는 move필요없이 바로 추가 가능.

// 인벤토리의 아이템 사용)
// sc()->displayInventory();
// sc()->useItemFromInventory(인벤토리 슬롯 번호);
// sc()->removeItemFromInventory(인벤토리 슬롯 번호);

// 인벤토리를 통하지 않고 바로 아이템 사용)
// sc()->useItem(makeCriticalBoost("하급 민첩성 영약",5,7);

// 플레이어 캐릭터는 사망 상태에 이르고 getIsDead() 함수로 이를 나타내지만 그 상태에 따른 동작제한은 하지않음. 
// 게임매니저에서 게임 종료처리 해주길 기대함.

#pragma once
#include<string>
#include<vector>
#include<memory>

class IItem;
class Weapon;
class Armor;
class IMonster;

class Character
{
public:
	static Character* getInstance();
	
	// 스탯에 대한 정보가 필요할 때
	std::string getName()const;
	int getLevel()const;
	int getExperience() const;
	int getHealth()const;
	int getMaxHealth() const;
	int getAttack()const;
	int getCritical()const;
	bool getIsDead() const;
	int getGold() const;
	Character* displayStatus() const;
	

	// 전투 시스템에서 실질적으로 변하는 값을 설정하는 함수들.
	Character* increaseExperience(int amount);
	Character* recovery(int amount);
	Character* recoveryToFullCondition(); // 회복시키지만 메세지를 띄우지 않아서 전투 시작 전이나 전투 종료 후에 호출하기 좋음.
	Character* attackToMonster(IMonster* target);
	Character* takeDamage(int amount);

	// 레벨, 장비 외 능력치 상승에 쓰이는 함수들. 레벨과 장비를 제외한 스탯 상승은 오직 이 함수들로 이루어져야함.
	// 현재 게임 시스템에선 오직 부스트 아이템만 이 함수들을 활용.
	Character* increaseAttackBoost(int amount);
	Character* decreaseAttackBoost(int amount);
	Character* increaseCriticalBoost(int increasePercent);
	Character* decreaseCriticalBoost(int decreasePercent);
	Character* increaseMaxHealthBoost(int amount);
	Character* decreaseMaxHealthBoost(int amount);

	// 골드 설정. 상점시스템에 활용하기 위함.
	Character* increaseGold(int amount);
	Character* decreaseGold(int amount);

	// 인벤토리 함수들.
	Character* displayInventory() const;
	IItem* getInventoryItem(int index) const;

	Character* addItemToInventory(std::unique_ptr<IItem> item);
	Character* removeItemFromInventory(int index);
	Character* useItemFromInventory(int index);
	Character* useILastIndexItemFromInventory();
	int getInventoryLength();

	// 인벤토리를 거치지 않고 바로 아이템을 사용.
	Character* useItem(std::unique_ptr<IItem> item);
	Character* equipWeapon(std::unique_ptr<Weapon> weapon);
	Character* unEquipWeapon();
	Character* equipArmor(std::unique_ptr<Armor> armor);
	Character* unEquipArmor();

	const Weapon* getEquipedWeapon() const;
	const Armor* getEquipedArmor() const;
	

private:
	// 싱글턴 인스턴스.
	static std::unique_ptr<Character> instance;

	// 싱글턴을 위한 생성자 숨기기 및 복사 방지.
	Character(const std::string& name, int level);
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;

	// 헬퍼 함수들.
	void levelUp();
	void calculateStat();
	void setHealth(int value);
	void setGold(int value);

	// 멤버 변수들.
	std::string name;
	int level;
	int health;
	int maxHealth;
	int attack;
	int criticalProbability;
	int experience;
	int gold;

	std::unique_ptr<Weapon> equipedWeapon;
	std::unique_ptr<Armor> equipedArmor;
	std::vector<std::unique_ptr<IItem>> inventory;

	int attackBoostAmount;
	int criticalBoostAmount;
	int maxHealthBoostAmount;


};


