#include "actor.h"

Actor::Actor() : hp(1), perceptionRadius(5), behaviour(nullptr), locatedOn(nullptr)
{

}

Actor::Actor(const string &name, const string &type, char symbol, int x, int y, int hp,
			 int perceptionRadius, AI *behaviour, Map *locatedOn) :
	Tile(name, type, symbol),
	hp(hp),
	x(x),
	y(y),
	perceptionRadius(perceptionRadius),
	behaviour(behaviour),
	locatedOn(locatedOn)
{
}

void Actor::draw(int indent)
{
	if (!isSeen)
		return;
	mvaddch(y + indent, x, symbol);
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

void Actor::takeTurn(Actor *player)
{
	behaviour->takeTurn(this, player);
}

void Actor::move(int x, int y)
{
	if (x > map_x - 1 || x < 0 || y > map_y - 1 || y < 0)
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

Map *Actor::getMap()
{
	return locatedOn;
}

void Actor::setAI(AI *behaviour)
{
	delete this->behaviour;
	this->behaviour = behaviour;
}

