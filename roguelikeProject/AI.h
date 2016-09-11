#pragma once

#include "actor.h"
#include "fieldOfView.h"

class Actor;
class AI
{
public:
    AI();
    virtual ~AI();
    virtual void takeTurn(Actor *actor, Actor *player) = 0;
};
