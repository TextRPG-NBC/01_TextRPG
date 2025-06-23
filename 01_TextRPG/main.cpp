#include <iostream>
#include "SCharacter.h"
#include "SItem.h"
#include "ItemManager.h""

int main()
{
    auto item = ItemManager::getInstance()->getRandomItem(5);

    Character::getInstance()->addItemToInventory(std::move(item))
    ->useILastIndexItemFromInventory()
    ->displayStatus();
    
    
    
}
