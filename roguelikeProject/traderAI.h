#pragma once

#include "citizenAI.h"

class TraderAI : public CitizenAI
{
public:
    TraderAI();
    void takeTurn(Actor *actor, Actor *player);
    int askPrice(Item *);
    string talk();
};
