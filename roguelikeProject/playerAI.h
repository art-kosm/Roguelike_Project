#pragma once

#include "AI.h"

class PlayerAI : public AI
{
public:
    PlayerAI();
    void takeTurn(Actor *, Actor *);
    int askPrice(Item *item);
};
