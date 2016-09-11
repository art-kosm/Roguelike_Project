#pragma once

#include "actor.h"
#include "item.h"

class AI
{
public:
    AI();
    virtual ~AI();
    virtual void takeTurn(Actor *actor, Actor *player) = 0;
    virtual int askPrice(Item *);
    virtual string talk();
};
