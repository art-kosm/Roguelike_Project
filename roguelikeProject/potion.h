#pragma once

#include "item.h"

class Potion : public Item
{
public:
    Potion();
    void useOn(Actor *actor);
};

