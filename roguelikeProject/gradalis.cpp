#include <limits>
#include "gradalis.h"
#include "actor.h"

Gradalis::Gradalis(const string &name, int x, int y) :
    Item(name, GRADALIS, 'T', false, false, x, y)
{}

void Gradalis::useOn(Actor *actor)
{
    actor->takeDamage(std::numeric_limits<int>::max());
}
