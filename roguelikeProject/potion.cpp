#include "potion.h"
#include "actor.h"

Potion::Potion() :
    Item("POTION", POTION, 'h')
{}

void Potion::useOn(Actor *actor)
{
    actor->restoreHP(rand() % 2 + 5);
}
