#include "actor.h"

Actor::Actor() : hp(1)
{

}

Actor::Actor(const string &name, const string &type, char symbol, int x, int y, int hp) :
	Tile(name, type, symbol),
	hp(hp),
	x(x),
	y(y)
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

	this->x = x;
	this->y = y;
}

