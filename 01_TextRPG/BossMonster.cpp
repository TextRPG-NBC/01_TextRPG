#include "BossMonster.h"
#include "RandomUtil.h"
#include <iostream>

BossMonster::BossMonster(int level)
{
    name = "Dragon";
    health = RandomUtil::getInt(level * 30, level * 45);
    attack = RandomUtil::getInt(level * 7, level * 15);

    std::cout << "몬스터 " << name << " 등장! " << "체력 : " << health << ", 공격력 : " << attack << std::endl;
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

Item* BossMonster::dropItem()
{
    return nullptr;
}
