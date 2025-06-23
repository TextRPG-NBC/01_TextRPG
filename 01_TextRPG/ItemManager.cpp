#include "ItemManager.h"
#include "SItem.h"
#include<iostream>
#include<iomanip>

#include "RandomUtil.h"

std::unique_ptr<ItemManager> ItemManager::instance = nullptr;

ItemManager* ItemManager::getInstance()
{
    if (!instance)
    {
        instance.reset(new ItemManager());
    }
    return instance.get();
}

ItemManager* ItemManager::displayAllItemList() const
{
    std::cout << "==== 아이템 목록 ====" << std::endl;
    int count = 0;
    
    for (const auto& item : weaponList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" << "[" << std::setw(20)<< std::right << item->getName() << "] :"
            << "공격력 증가(" << item->getAttackBonus() << "), "
            << "치명타 증가(" << item->getCriticalBonus() << "),"
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }

    for (const auto& item : armorList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" <<  "[" << std::setw(20) << std::right <<item->getName() << "] :"
            << "최대체력 증가(" << item->getMaxHealthBonus() << "), "
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }

    for (const auto& item : attackBoostList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" << std::setw(20) <<std::right << item->getName() << "] :"
            << "공격력 영구 증가(" << item->getBoostAmount() << "), "
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }

    for (const auto& item : criticalBoostList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" << std::setw(20) <<std::right << item->getName() << "] :"
            << "치명타율 영구 증가(" << item->getBoostAmount() << "), "
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }

    for (const auto& item : maxHealthBoostList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" << std::setw(20) <<std::right << item->getName() << "] :"
            << "최대체력 영구 증가(" << item->getBoostAmount() << "), "
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }

    for (const auto& item : healthPotionList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" << std::setw(20) <<std::right << item->getName() << "] :"
            << "회복량(" << item->getHealAmount() << "), "
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }
    return instance.get();
}

ItemManager* ItemManager::displayWeaponList() const
{
    std::cout << "==== 무기 아이템 목록 ====" << std::endl;
    _displayWeaponList();
    return instance.get();
}

ItemManager* ItemManager::displayArmorList() const
{
    std::cout << "==== 갑옷 아이템 목록 ====" << std::endl;
    _displayArmorList();
    return instance.get();
}

ItemManager* ItemManager::displayAttackBoostList() const
{
    std::cout << "==== 공격력 부스트 아이템 목록 ====" << std::endl;
    _displayAttackBoostList();
    return instance.get();
}

ItemManager* ItemManager::displayCriticalBoostList() const
{
    std::cout << "==== 치명타율 부스트 아이템 목록 ====" << std::endl;
    _displayCriticalBoostList();
    return instance.get();
}

ItemManager* ItemManager::displayMaxHealthBoostList() const
{
    std::cout << "==== 최대 체력 부스트 아이템 목록 ====" << std::endl;
    _displayMaxHealthBoostList();
    return instance.get();
}

ItemManager* ItemManager::displayHealthPotionList() const
{
    std::cout << "==== 회복 물약 부스트 아이템 목록 ====" << std::endl;
    _displayHealthPotionList();
    return instance.get();
}

const std::vector<std::unique_ptr<IItem>>& ItemManager::getAllItemList() const
{
    return allItemList;
}

const std::vector<std::unique_ptr<Weapon>>& ItemManager::getWeaponList() const
{
    return weaponList;
}

const std::vector<std::unique_ptr<Armor>>& ItemManager::getArmorList() const
{
    return armorList;
}

const std::vector<std::unique_ptr<AttackBoost>>& ItemManager::getAttackBoostList() const
{
    return attackBoostList;
}

const std::vector<std::unique_ptr<CriticalBoost>>& ItemManager::getCriticalBoostList() const
{
    return criticalBoostList;
}

const std::vector<std::unique_ptr<MaxHealthBoost>>& ItemManager::getMaxHealthBoostList() const
{
    return maxHealthBoostList;
}

const std::vector<std::unique_ptr<HealthPotion>>& ItemManager::getHealthPotionList() const
{
    return healthPotionList;
}

// std::unique_ptr<Weapon> ItemManager::getRandomWeapon(int level) const
// {
//     int random = RandomUtil::getInt(0,6);
//     
// }
//
// std::unique_ptr<Armor> ItemManager::getRandomArmor(int level) const
// {
// }
//
// std::unique_ptr<AttackBoost> ItemManager::getRandomAttackBoost(int level) const
// {
// }
//
// std::unique_ptr<CriticalBoost> ItemManager::getRandomCriticalBoost(int level) const
// {
// }
//
// std::unique_ptr<MaxHealthBoost> ItemManager::getRandomMaxHealthBoost(int level) const
// {
// }
//
// std::unique_ptr<HealthPotion> ItemManager::getRandomHealthPotion(int level) const
// {
// }

std::unique_ptr<IItem> ItemManager::getRandomItem(int level) const
{
    int itemLevel = (level-1) + RandomUtil::getInt(-1, 1);
    if (itemLevel<0) itemLevel = 0;
    if (itemLevel>9) itemLevel = 9;
    
    int itemType = RandomUtil::getInt(1, 6);

    std::unique_ptr<IItem> item;
    switch (itemType)
    {
    case 1:
        item = weaponList.at(itemLevel)->clone();
        break;
    case 2:
        item = armorList.at(itemLevel)->clone();
        break;
    case 3:
        item = attackBoostList.at(itemLevel)->clone();
        break;
    case 4:
        item = criticalBoostList.at(itemLevel)->clone();
        break;
    case 5:
        item = maxHealthBoostList.at(itemLevel)->clone();
        break;
    case 6:
        item = healthPotionList.at(itemLevel)->clone();
        break;
    default:
        return nullptr;
        break;
    }
    
    return std::move(item);
}



ItemManager::ItemManager()
{
    weaponList.push_back(makeWeapon("나뭇가지",5,2,10));
    weaponList.push_back(makeWeapon("몽둥이",10,10,30));
    weaponList.push_back(makeWeapon("단검",10,50,50));
    weaponList.push_back(makeWeapon("장검",30,35,80));
    weaponList.push_back(makeWeapon("장창",40,25,100));
    weaponList.push_back(makeWeapon("의천검",40,50,200));
    weaponList.push_back(makeWeapon("청령언월도",100,10,300));
    weaponList.push_back(makeWeapon("방천화극",110,50,400));
    weaponList.push_back(makeWeapon("가로등",200,1,600));
    weaponList.push_back(makeWeapon("k-2",500,100,1000));

    armorList.push_back(makeArmor("누더기 천 조각",30,10));
    armorList.push_back(makeArmor("천 갑옷",70,30));
    armorList.push_back(makeArmor("가죽 갑옷",100,50));
    armorList.push_back(makeArmor("사슬 갑옷",150,80));
    armorList.push_back(makeArmor("백은 갑옷",200,130));
    armorList.push_back(makeArmor("황금 갑옷",250,200));
    armorList.push_back(makeArmor("용린 갑옷",300,350));
    armorList.push_back(makeArmor("가시 갑옷",350,400));
    armorList.push_back(makeArmor("망자의 갑옷",400,450));
    armorList.push_back(makeArmor("워모그의 갑옷",800,500));

    attackBoostList.push_back(makeAttackBoost("1 단계 공격력 영약",5,15));
    attackBoostList.push_back(makeAttackBoost("2 단계 공격력 영약",7,21));
    attackBoostList.push_back(makeAttackBoost("3 단계 공격력 영약",9,27));
    attackBoostList.push_back(makeAttackBoost("4 단계 공격력 영약",11,33));
    attackBoostList.push_back(makeAttackBoost("5 단계 공격력 영약",13,39));
    attackBoostList.push_back(makeAttackBoost("6 단계 공격력 영약",15,45));
    attackBoostList.push_back(makeAttackBoost("7 단계 공격력 영약",17,51));
    attackBoostList.push_back(makeAttackBoost("8 단계 공격력 영약",19,57));
    attackBoostList.push_back(makeAttackBoost("9 단계 공격력 영약",21,63));
    attackBoostList.push_back(makeAttackBoost("10 단계 공격력 영약",25,70));
    
    criticalBoostList.push_back(makeCriticalBoost("1 단계 치명타 영약",1,12));
    criticalBoostList.push_back(makeCriticalBoost("2 단계 치명타 영약",2,22));
    criticalBoostList.push_back(makeCriticalBoost("3 단계 치명타 영약",3,32));
    criticalBoostList.push_back(makeCriticalBoost("4 단계 치명타 영약",4,42));
    criticalBoostList.push_back(makeCriticalBoost("5 단계 치명타 영약",5,52));
    criticalBoostList.push_back(makeCriticalBoost("6 단계 치명타 영약",6,62));
    criticalBoostList.push_back(makeCriticalBoost("7 단계 치명타 영약",7,72));
    criticalBoostList.push_back(makeCriticalBoost("8 단계 치명타 영약",8,82));
    criticalBoostList.push_back(makeCriticalBoost("9 단계 치명타 영약",9,92));
    criticalBoostList.push_back(makeCriticalBoost("10 단계 치명타 영약",10,102));

    maxHealthBoostList.push_back(makeMaxHealthBoost("1단계 생명력 영약",15,15));
    maxHealthBoostList.push_back(makeMaxHealthBoost("2단계 생명력 영약",30,21));
    maxHealthBoostList.push_back(makeMaxHealthBoost("3단계 생명력 영약",45,27));
    maxHealthBoostList.push_back(makeMaxHealthBoost("4단계 생명력 영약",60,33));
    maxHealthBoostList.push_back(makeMaxHealthBoost("5단계 생명력 영약",75,39));
    maxHealthBoostList.push_back(makeMaxHealthBoost("6단계 생명력 영약",90,45));
    maxHealthBoostList.push_back(makeMaxHealthBoost("7단계 생명력 영약",105,51));
    maxHealthBoostList.push_back(makeMaxHealthBoost("8단계 생명력 영약",120,57));
    maxHealthBoostList.push_back(makeMaxHealthBoost("9단계 생명력 영약",135,63));
    maxHealthBoostList.push_back(makeMaxHealthBoost("10단계 생명력 영약",150,70));

    healthPotionList.push_back(makeHealthPotion("1 단계 회복 물약",10,3));
    healthPotionList.push_back(makeHealthPotion("2 단계 회복 물약",30,10));
    healthPotionList.push_back(makeHealthPotion("3 단계 회복 물약",60,25));
    healthPotionList.push_back(makeHealthPotion("4 단계 회복 물약",100,50));
    healthPotionList.push_back(makeHealthPotion("5 단계 회복 물약",150,80));
    healthPotionList.push_back(makeHealthPotion("6 단계 회복 물약",200,100));
    healthPotionList.push_back(makeHealthPotion("7 단계 회복 물약",250,120));
    healthPotionList.push_back(makeHealthPotion("8 단계 회복 물약",300,150));
    healthPotionList.push_back(makeHealthPotion("9 단계 회복 물약",400,200));
    healthPotionList.push_back(makeHealthPotion("10 단계 회복 물약",500,250));

    
    allItemList.push_back(makeWeapon("나뭇가지",5,2,10));
    allItemList.push_back(makeWeapon("몽둥이",10,10,30));
    allItemList.push_back(makeWeapon("단검",10,50,50));
    allItemList.push_back(makeWeapon("장검",30,35,80));
    allItemList.push_back(makeWeapon("장창",40,25,100));
    allItemList.push_back(makeWeapon("의천검",40,50,200));
    allItemList.push_back(makeWeapon("청령언월도",100,10,300));
    allItemList.push_back(makeWeapon("방천화극",110,50,400));
    allItemList.push_back(makeWeapon("가로등",200,1,600));
    allItemList.push_back(makeWeapon("k-2",500,100,1000));

    allItemList.push_back(makeArmor("누더기 천 조각",30,10));
    allItemList.push_back(makeArmor("천 갑옷",70,30));
    allItemList.push_back(makeArmor("가죽 갑옷",100,50));
    allItemList.push_back(makeArmor("사슬 갑옷",150,80));
    allItemList.push_back(makeArmor("백은 갑옷",200,130));
    allItemList.push_back(makeArmor("황금 갑옷",250,200));
    allItemList.push_back(makeArmor("용린 갑옷",300,350));
    allItemList.push_back(makeArmor("가시 갑옷",350,400));
    allItemList.push_back(makeArmor("망자의 갑옷",400,450));
    allItemList.push_back(makeArmor("워모그의 갑옷",800,500));

    allItemList.push_back(makeAttackBoost("1 단계 공격력 영약",5,15));
    allItemList.push_back(makeAttackBoost("2 단계 공격력 영약",7,21));
    allItemList.push_back(makeAttackBoost("3 단계 공격력 영약",9,27));
    allItemList.push_back(makeAttackBoost("4 단계 공격력 영약",11,33));
    allItemList.push_back(makeAttackBoost("5 단계 공격력 영약",13,39));
    allItemList.push_back(makeAttackBoost("6 단계 공격력 영약",15,45));
    allItemList.push_back(makeAttackBoost("7 단계 공격력 영약",17,51));
    allItemList.push_back(makeAttackBoost("8 단계 공격력 영약",19,57));
    allItemList.push_back(makeAttackBoost("9 단계 공격력 영약",21,63));
    allItemList.push_back(makeAttackBoost("10 단계 공격력 영약",25,70));
    
    allItemList.push_back(makeCriticalBoost("1 단계 치명타 영약",1,12));
    allItemList.push_back(makeCriticalBoost("2 단계 치명타 영약",2,22));
    allItemList.push_back(makeCriticalBoost("3 단계 치명타 영약",3,32));
    allItemList.push_back(makeCriticalBoost("4 단계 치명타 영약",4,42));
    allItemList.push_back(makeCriticalBoost("5 단계 치명타 영약",5,52));
    allItemList.push_back(makeCriticalBoost("6 단계 치명타 영약",6,62));
    allItemList.push_back(makeCriticalBoost("7 단계 치명타 영약",7,72));
    allItemList.push_back(makeCriticalBoost("8 단계 치명타 영약",8,82));
    allItemList.push_back(makeCriticalBoost("9 단계 치명타 영약",9,92));
    allItemList.push_back(makeCriticalBoost("10 단계 치명타 영약",10,102));

    allItemList.push_back(makeMaxHealthBoost("1단계 생명력 영약",15,15));
    allItemList.push_back(makeMaxHealthBoost("2단계 생명력 영약",30,21));
    allItemList.push_back(makeMaxHealthBoost("3단계 생명력 영약",45,27));
    allItemList.push_back(makeMaxHealthBoost("4단계 생명력 영약",60,33));
    allItemList.push_back(makeMaxHealthBoost("5단계 생명력 영약",75,39));
    allItemList.push_back(makeMaxHealthBoost("6단계 생명력 영약",90,45));
    allItemList.push_back(makeMaxHealthBoost("7단계 생명력 영약",105,51));
    allItemList.push_back(makeMaxHealthBoost("8단계 생명력 영약",120,57));
    allItemList.push_back(makeMaxHealthBoost("9단계 생명력 영약",135,63));
    allItemList.push_back(makeMaxHealthBoost("10단계 생명력 영약",150,70));

    allItemList.push_back(makeHealthPotion("1 단계 회복 물약",10,3));
    allItemList.push_back(makeHealthPotion("2 단계 회복 물약",30,10));
    allItemList.push_back(makeHealthPotion("3 단계 회복 물약",60,25));
    allItemList.push_back(makeHealthPotion("4 단계 회복 물약",100,50));
    allItemList.push_back(makeHealthPotion("5 단계 회복 물약",150,80));
    allItemList.push_back(makeHealthPotion("6 단계 회복 물약",200,100));
    allItemList.push_back(makeHealthPotion("7 단계 회복 물약",250,120));
    allItemList.push_back(makeHealthPotion("8 단계 회복 물약",300,150));
    allItemList.push_back(makeHealthPotion("9 단계 회복 물약",400,200));
    allItemList.push_back(makeHealthPotion("10 단계 회복 물약",500,250));
}

void ItemManager::_displayWeaponList() const
{
    int count = 0;
    for (const auto& item : weaponList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" << std::setw(20) << item->getName() << "] :"
            << "공격력 증가(" << item->getAttackBonus() << "), "
            << "치명타 증가(" << item->getCriticalBonus() << "),"
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }
    
}

void ItemManager::_displayArmorList() const
{
    int count = 0;
    std::cout << std::right;
    for (const auto& item : armorList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" << std::setw(20) <<item->getName() << "] :"
            << "최대체력 증가(" << item->getMaxHealthBonus() << "), "
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }
}

void ItemManager::_displayAttackBoostList() const
{
    int count =0;
    std::cout << std::right;
    for (const auto& item : attackBoostList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" <<  std::setw(20) << item->getName() << "] :"
            << "공격력 영구 증가(" << item->getBoostAmount() << "), "
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }
}

void ItemManager::_displayCriticalBoostList() const
{
    int count = 0;
    std::cout << std::right;
    for (const auto& item : criticalBoostList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" << std::setw(20) << item->getName() << "] :"
            << "치명타율 영구 증가(" << item->getBoostAmount() << "), "
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }
}

void ItemManager::_displayMaxHealthBoostList() const
{
    int count =0;
    std::cout << std::right;
    for (const auto& item : maxHealthBoostList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" <<  std::setw(20) << item->getName() << "] :"
            << "최대체력 영구 증가(" << item->getBoostAmount() << "), "
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }
}

void ItemManager::_displayHealthPotionList() const
{
    int count = 0;
    std::cout << std::right;
    for (const auto& item : healthPotionList)
    {
        std::cout << "[" <<std::setw(2)<<count<<"]" << std::setw(20) << item->getName() << "] :"
            << "회복량(" << item->getHealAmount() << "), "
            << "가격(" << item->getPrice() << ")" << std::endl;
        count++;
    }
}
