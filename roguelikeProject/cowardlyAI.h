#pragma once

#include "AI.h"

class CowardlyAI : public AI
{
public:
    CowardlyAI();
    void takeTurn(Actor *actor, Actor *player);

private:
    int distance(int actorX, int actorY, int playerX, int playerY);
};

