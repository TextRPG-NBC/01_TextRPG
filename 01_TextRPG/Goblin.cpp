#include "Goblin.h"
#include <random>

Goblin::Goblin(int level)
{
    name = "Goblin";

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> healthDist(level * 20, level * 30);
    std::uniform_int_distribution<> attackDist(level * 5, level * 10);

    health = healthDist(gen);
    attack = attackDist(gen);
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
