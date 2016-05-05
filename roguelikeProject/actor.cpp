#include "actor.h"

Actor::Actor() : hp(1), locatedOn(nullptr)
{

}

Actor::Actor(const string &name, const string &type, char symbol, int x, int y, int hp, Map *locatedOn) :
	Tile(name, type, symbol),
	hp(hp),
	x(x),
	y(y),
	locatedOn(locatedOn)
{
}

void Actor::draw()
{
	mvaddch(y, x, symbol);
}

int Actor::getX()
{
	return x;
}

int Actor::getY()
{
	return y;
}

void Actor::move(int x, int y)
{
	if (x > term_x - 1 || x < 0 || y > term_y - 1 || y < 0)
		return;

	if (locatedOn->tileIsOccupied(x, y) || !locatedOn->tileIsPassable(x, y))
		return;

	this->x = x;
	this->y = y;
}

void Actor::setMap(Map *map)
{
	locatedOn = map;
}

