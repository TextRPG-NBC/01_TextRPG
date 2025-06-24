#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Item.h"

class Monster;
class IWeapon;
class IArmor;


class Player
{
private:
	/* Singleton instance */
	static std::unique_ptr<Player> instance;
	Player(const std::string& name);			// Hide Constructor

	std::string name;
	int level, maxHP, curHP, attack, exp, gold, criticalProbability = 0;
	int tempAttackBuff = 0, tempCriticalProbability = 0;
	std::vector<std::unique_ptr<Item>> inventory;

	std::unique_ptr<Item> equippingWeapon;
	std::unique_ptr<Item> equippingArmor;



public:
	static Player& getInstance(const std::string& name = "Hero");
	Player(const Player&) = delete;				// Delete Copy Constructor
	Player& operator=(const Player&) = delete;	// Delete Copy Assignment
	


	void showStatus() const;
	void resetTempAbility();
	void useItem();
	void useItemUsingIndex(int index);
	void attackMonster(Monster& monster);
	void takeDamage(int damage);
	void addExp(int amount);
	void addGold(int amount);

	void increaseAttack(int amount);
	void increaseCriticalProbability(int amount);
	void increaseCurrentHP(int amount);
	void increaseMaxHP(int amount);

	void decreaseAttack(int amount);
	void decreaseCriticalProbability(int amount);
	void decreaseMaxHP(int amount);
	
	void subtractGold(int amount);
	void addItem(std::unique_ptr<Item> item);
	void healHP(int amount);
	void addTempAttack(int amount);
	void addTempCriticalProbability(int amount);
	void removeItemByIdx(int idx);
	void displayInventory();
	bool isAlive() const;
	bool hasConsumable() const;
	int getLevel() const;
	int getGold() const;
	int getExp() const;
	int getCurrentHP() const;
	int getMaxHP() const;
	std::string getName() const;
	std::vector<std::unique_ptr<Item>>& getInventory();
	
	void equipWeapon(std::unique_ptr<Item> weapon);
	void equipArmor(std::unique_ptr<Item> armor);
	void unEquipWeapon();
	void unEquipArmor();

/* 내부 호출용 함수 */
private:
	int getAttackDamage() const;
	int getCriticalProbability() const;
	void levelUp();
};