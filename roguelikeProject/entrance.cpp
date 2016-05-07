#include "entrance.h"

Entrance::Entrance() : x(0), y(0), symbol('>'), leadsFrom(nullptr), leadsTo(nullptr), isSeen(false), isRemembered(false)
{
}

Entrance::Entrance(int x, int y, char symbol, Map *leadsFrom, Map *leadsTo, bool isSeen, bool isRemembered) :
	x(x),
	y(y),
	symbol(symbol),
	leadsFrom(leadsFrom),
	leadsTo(leadsTo),
	isSeen(isSeen),
	isRemembered(isRemembered)
{
}

Entrance::~Entrance()
{
	/*if (leadsTo->getEntrancesNumber() == 1)
		delete leadsTo;*/
}

void Entrance::draw()
{
	if (!isRemembered)
		return;
	if (!isSeen)
		attron(A_DIM);

	mvaddch(y, x, symbol);
	attroff(A_DIM);
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

void Entrance::setSeen(bool status)
{
	isSeen = status;
	if (isSeen)
		isRemembered = true;
}

