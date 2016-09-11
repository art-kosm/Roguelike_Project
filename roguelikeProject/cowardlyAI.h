#pragma once

#include "AI.h"

class Actor;
class CowardlyAI : public AI
{
public:
    CowardlyAI();
    void takeTurn(Actor *actor, Actor *player);
};

