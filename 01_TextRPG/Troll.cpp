#include "Troll.h"
#include "RandomUtil.h"
#include <iostream>

Troll::Troll(int level)
{
    name = "Troll";
    health = RandomUtil::getInt(level * 20, level * 30);
    attack = RandomUtil::getInt(level * 5, level * 10);

    std::cout << "몬스터 " << name << " 등장! " << "체력 : " << health << ", 공격력 : " << attack << std::endl;
}

string Troll::getName()
{
    return name;
}

int Troll::getHealth()
{
    return health;
}

int Troll::getAttack()
{
    return attack;
}

void Troll::takeDamage(int damage)
{
    health -= damage;

    if (health < 0)
    {
        health = 0;
    }
}

Item* Troll::dropItem()
{
    return nullptr;
}
