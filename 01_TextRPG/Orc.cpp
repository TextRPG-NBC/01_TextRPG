#include "Orc.h"
#include <random>

Orc::Orc(int level)
{
    name = "Orc";

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> healthDist(level * 20, level * 30);
    std::uniform_int_distribution<> attackDist(level * 5, level * 10);

    health = healthDist(gen);
    attack = attackDist(gen);
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
