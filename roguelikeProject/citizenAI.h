#pragma once

#include "AI.h"

class CitizenAI : public AI
{
public:
    CitizenAI();
    virtual void takeTurn(Actor *actor, Actor *);
    virtual string talk();
};
