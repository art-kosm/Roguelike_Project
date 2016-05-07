#include "actor.h"

Actor::Actor() : hp(1), perceptionRadius(5), locatedOn(nullptr)
{

}

Actor::Actor(const string &name, const string &type, char symbol, int x, int y, int hp,
			 int perceptionRadius, Map *locatedOn) :
	Tile(name, type, symbol),
	hp(hp),
	x(x),
	y(y),
	perceptionRadius(perceptionRadius),
	locatedOn(locatedOn)
{
}

void Actor::draw()
{
	if (!isSeen)
		return;
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

int Actor::getPerceptionRadius()
{
	return perceptionRadius;
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

