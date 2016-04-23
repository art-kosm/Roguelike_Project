#include "actor.h"

Actor::Actor() : hp(1)
{

}

Actor::Actor(string name, string type, char symbol, int x, int y, int hp) : MapElement(name, type, symbol), hp(hp), x(x), y(y)
{

}

int Actor::getX()
{
	return x;
}

int Actor::getY()
{
	return y;
}

void Actor::setX(int x)
{
	this->x = x;
}

void Actor::setY(int y)
{
	this->y = y;
}

