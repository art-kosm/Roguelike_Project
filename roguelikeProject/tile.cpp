#include "tile.h"

Tile::Tile() : name ("default"), symbol('.'), isSeen(false), isRemembered(false)
{
}

Tile::Tile(const string &name, const string &type, char symbol, bool isSeen, bool isRemembered) :
	name(name), type(type), symbol(symbol), isSeen(isSeen), isRemembered(isRemembered)
{
}

Tile::~Tile()
{

}

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

	mvaddch(y, x, symbol);

	attroff(A_BOLD);
	attroff(A_DIM);
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


