#pragma once

#include "AI.h"

class Actor;
class AggressiveAI : public AI
{
public:
    AggressiveAI();
    void takeTurn(Actor *actor, Actor *player);
};
