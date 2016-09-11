#include "playerAI.h"

PlayerAI::PlayerAI()
{}

void PlayerAI::takeTurn(Actor *, Actor *)
{}

int PlayerAI::askPrice(Item *item)
{
    if (item->getType() == WEAPON)
    {
        Weapon *weapon = dynamic_cast<Weapon *>(item);
        return weapon->getDamage() * 2;
    }

    return 5;
}
