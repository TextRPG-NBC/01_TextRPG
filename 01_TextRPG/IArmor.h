#pragma once
#include <memory>
class Player;
class IArmor
{

public:
    virtual void equipped(Player& player) = 0; 
    virtual void unEquipped(Player& player) = 0;

    IArmor() = default;
    virtual ~IArmor() = default;   
};