#include "item.h"

Item::Item(const std::string &name, const std::string &type, char symbol, bool isSeen, bool isRemembered, int x, int y) :
    Tile(name, type, symbol, isSeen, isRemembered), x(x), y(y)
{

}

void Item::draw(int indent)
{
    if (!isRemembered)
        return;

    if (isSeen)
        attron(A_BOLD);
    else
        attron(A_DIM);

    mvaddch(y + indent, x, symbol);

    attroff(A_BOLD);
    attroff(A_DIM);
}

void Item::setX(int x)
{
    this->x = x;
}

void Item::setY(int y)
{
    this->y = y;
}

int Item::getX()
{
    return x;
}

int Item::getY()
{
    return y;
}

