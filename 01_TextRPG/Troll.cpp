#include "Troll.h"

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
