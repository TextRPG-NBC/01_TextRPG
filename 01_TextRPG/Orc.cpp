#include "Orc.h"

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
