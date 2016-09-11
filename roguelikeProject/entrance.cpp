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
{}

Entrance::~Entrance()
{}

void Entrance::draw(int indent)
{
    if (!isRemembered)
        return;
    if (!isSeen)
        attron(A_DIM);

    if (symbol == 'O')
        attron(COLOR_PAIR(2));

    mvaddch(y + indent, x, symbol);
    attroff(A_DIM);

    attroff(COLOR_PAIR(2));
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

void Entrance::setLeadsTo(Map *map)
{
    leadsTo = map;
}

