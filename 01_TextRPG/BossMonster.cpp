#include "BossMonster.h"
#include "RandomUtil.h"
#include <iostream>
#include "IItem.h"
#include "ItemManager.h"

BossMonster::BossMonster(int level)
{
    name = "Dragon";
    health = RandomUtil::getInt(level * 30, level * 45);
    attack = RandomUtil::getInt(level * 7, level * 15);
    item = ItemManager::getInstance()->getRandomItem(level);

    cout << "몬스터 " << name << " 등장! " << "체력 : " << health << ", 공격력 : " << attack << std::endl;
}

string BossMonster::getName()
{
    return name;
}

int BossMonster::getHealth()
{
    return health;
}

int BossMonster::getAttack()
{
    return attack;
}

void BossMonster::takeDamage(int damage)
{
    health -= damage;

    if (health < 0)
    {
        health = 0;
    }
}

unique_ptr<IItem> BossMonster::dropItem()
{
    cout << name << "이(가) " << item->getName() << " 아이템을 드랍했습니다" << endl;
    return move(item);
}
