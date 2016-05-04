#include "entrance.h"

Entrance::Entrance() : x(0), y(0), symbol('>'), leadsFrom(nullptr), leadsTo(nullptr)
{
}

Entrance::Entrance(int x, int y, char symbol, Map *leadsFrom, Map *leadsTo) :
	x(x),
	y(y),
	symbol(symbol),
	leadsFrom(leadsFrom),
	leadsTo(leadsTo)
{
}

Entrance::~Entrance()
{
	/*if (leadsTo->getEntrancesNumber() == 1)
		delete leadsTo;*/
}

void Entrance::draw()
{
	mvaddch(y, x, symbol);
}

int Entrance::getX()
{
	return x;
}

int Entrance::getY()
{
	return y;
}

Map *Entrance::getLeadsTo()
{
	return leadsTo;
}

Map *Entrance::getLeadsFrom()
{
	return leadsFrom;
}

