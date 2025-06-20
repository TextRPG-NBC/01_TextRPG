#include "Goblin.h"

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
