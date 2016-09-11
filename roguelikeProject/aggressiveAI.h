#pragma once

#include "AI.h"

class AggressiveAI : public AI
{
public:
    AggressiveAI();
    void takeTurn(Actor *actor, Actor *player);
};
