#include "tile.h"

Tile::Tile() : name ("default"), symbol('.'), isSeen(false), isRemembered(false)
{}

Tile::Tile(const string &name, Type type, char symbol, bool isSeen, bool isRemembered) :
    name(name), type(type), symbol(symbol), isSeen(isSeen), isRemembered(isRemembered)
{}

Tile::~Tile()
{}

void Tile::draw(int x , int y)
{
    if (!isRemembered)
    {
        mvaddch(y, x, ' ');
        return;
    }

    if (isSeen)
        attron(A_BOLD);
    else
        attron(A_DIM);

    if (type == GRASS)
        attron(COLOR_PAIR(1));
    else if (type == WATER)
        attron(COLOR_PAIR(4));

    mvaddch(y, x, symbol);

    attroff(A_BOLD);
    attroff(A_DIM);
    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(4));
}

char Tile::getSymbol()
{
    return symbol;
}

void Tile::setSeen(bool status)
{
    isSeen = status;
    if (isSeen)
        isRemembered = true;
}

void Tile::setRemembered(bool status)
{
    isRemembered = status;
}

const std::string &Tile::getName()
{
    return name;
}

Type Tile::getType()
{
    return type;
}


