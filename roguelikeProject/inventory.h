#pragma once

#include <vector>

#include "item.h"
#include "weapon.h"
#include "armor.h"

using std::vector;

class Inventory
{
public:
    Inventory();
    void addItem(Item *item);
    void equipWeapon(Weapon *weapon);
    void equipArmor(Armor *armor);
    void removeItem(Item *item);
    bool hasItem(Item *item);
    vector<Item *> getItems();
    Weapon *getEquippedWeapon();
    Armor *getEquippedArmor();

private:
    Weapon *equippedWeapon;
    Armor *equippedArmor;
    vector<Item *> items;
};

