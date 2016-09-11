#pragma once

#include "item.h"

class Weapon : public Item
{
public:
    Weapon(const string &name, int damage = 0, int x = 0, int y = 0);
    void useOn(Actor *actor);

private:
    int damage;
};

