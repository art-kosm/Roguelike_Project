#include "actor.h"

Actor::Actor() : hp(1)
{

}

Actor::Actor(std::string name, char symbol, int x, int y, int hp) : MapElement(name, symbol, x, y), hp(hp)
{

}

