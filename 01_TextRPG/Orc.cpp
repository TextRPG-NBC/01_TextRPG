#include "Orc.h"
#include "RandomUtil.h"
#include <iostream>

Orc::Orc(int level)
{
    name = "Orc";
    health = RandomUtil::getInt(level * 20, level * 30);
    attack = RandomUtil::getInt(level * 5, level * 10);

    std::cout << "몬스터 " << name << " 등장! " << "체력 : " << health << ", 공격력 : " << attack << std::endl;
}

string Orc::getName()
{
    return name;
}

int Orc::getHealth()
{
    return health;
}

int Orc::getAttack()
{
    return attack;
}

void Orc::takeDamage(int damage)
{
    health -= damage;

    if (health < 0)
    {
        health = 0;
    }
}

Item* Orc::dropItem()
{
    return nullptr;
}
