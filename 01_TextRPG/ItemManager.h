#pragma once

#include <memory>
#include <vector>

class Weapon;
class Armor;
class AttackBoost;
class CriticalBoost;
class MaxHealthBoost;
class HealthPotion;
class IItem;

class ItemManager
{
public:
    static ItemManager* getInstance();

    ItemManager* displayAllItemList() const;
    ItemManager* displayWeaponList() const;
    ItemManager* displayArmorList() const;
    ItemManager* displayAttackBoostList() const;
    ItemManager* displayCriticalBoostList() const;
    ItemManager* displayMaxHealthBoostList() const;
    ItemManager* displayHealthPotionList() const;

    const std::vector<std::unique_ptr<IItem>>& getAllItemList() const;
    const std::vector<std::unique_ptr<Weapon>>& getWeaponList() const;
    const std::vector<std::unique_ptr<Armor>>& getArmorList() const;
    const std::vector<std::unique_ptr<AttackBoost>>& getAttackBoostList() const;
    const std::vector<std::unique_ptr<CriticalBoost>>& getCriticalBoostList() const;
    const std::vector<std::unique_ptr<MaxHealthBoost>>& getMaxHealthBoostList() const;
    const std::vector<std::unique_ptr<HealthPotion>>& getHealthPotionList() const;
    
    // 랜덤 함수
    // std::unique_ptr<Weapon> getRandomWeapon(int level) const;
    // std::unique_ptr<Armor> getRandomArmor(int level) const;
    // std::unique_ptr<AttackBoost> getRandomAttackBoost(int level) const;
    // std::unique_ptr<CriticalBoost> getRandomCriticalBoost(int level) const;
    // std::unique_ptr<MaxHealthBoost> getRandomMaxHealthBoost(int level) const;
    // std::unique_ptr<HealthPotion> getRandomHealthPotion(int level) const;
    std::unique_ptr<IItem> getRandomItem(int level) const;

private:
    static std::unique_ptr<ItemManager> instance;
    
    ItemManager();
    ItemManager(const ItemManager&) = delete;
    ItemManager& operator=(const ItemManager&) = delete;
    
    void _displayWeaponList() const;
    void _displayArmorList() const;
    void _displayAttackBoostList() const;
    void _displayCriticalBoostList() const;
    void _displayMaxHealthBoostList() const;
    void _displayHealthPotionList() const;
    
    std::vector<std::unique_ptr<Weapon>> weaponList;
    std::vector<std::unique_ptr<Armor>> armorList;
    std::vector<std::unique_ptr<AttackBoost>> attackBoostList;
    std::vector<std::unique_ptr<CriticalBoost>> criticalBoostList;
    std::vector<std::unique_ptr<MaxHealthBoost>> maxHealthBoostList;
    std::vector<std::unique_ptr<HealthPotion>> healthPotionList;
    std::vector<std::unique_ptr<IItem>> allItemList;
    
};

