#include "Troll.h"
#include <random>

Troll::Troll(int level)
{
    name = "Troll";

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> healthDist(level * 20, level * 30);
    std::uniform_int_distribution<> attackDist(level * 5, level * 10);

    health = healthDist(gen);
    attack = attackDist(gen);
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
