#include "Goblin.h"
#include "RandomUtil.h"
#include <iostream>

Goblin::Goblin(int level)
{
    name = "Goblin";
    health = RandomUtil::getInt(level * 20, level * 30);
	attack = RandomUtil::getInt(level * 5, level * 10);

	std::cout << "몬스터 " << name << " 등장! " << "체력 : " << health << ", 공격력 : " << attack << std::endl;
}

string Goblin::getName()
{
    return name;
}

int Goblin::getHealth()
{
    return health;
}

int Goblin::getAttack()
{
    return attack;
}

void Goblin::takeDamage(int damage)
{
    health -= damage;

    if (health < 0) 
    {
        health = 0;
    }
}

Item* Goblin::dropItem()
{
    return nullptr;
}
