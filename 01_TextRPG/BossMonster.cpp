#include "BossMonster.h"

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
