#pragma once
#include <memory>

class Player;
class IWeapon
{

public:

    virtual void equipped(Player& player) = 0; 
    virtual void unEquipped(Player& player) = 0;

    IWeapon() = default;
    virtual ~IWeapon() = default;    
};