#include "BossMonster.h"
#include <random>

BossMonster::BossMonster(int level)
{
    name = "Dragon";

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> healthDist(level * 30, level * 45);
    std::uniform_int_distribution<> attackDist(level * 7, level * 15);

    health = healthDist(gen);
    attack = attackDist(gen);
}

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
