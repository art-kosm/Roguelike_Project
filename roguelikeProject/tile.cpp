#include "tile.h"

Tile::Tile() : name ("default"), symbol('.')
{
}

Tile::Tile(const string &name, const string &type, char symbol) : name(name), type(type), symbol(symbol)
{
}

Tile::~Tile()
{

}

void Tile::draw(int x , int y)
{
	mvaddch(y, x, symbol);
}

char Tile::getSymbol()
{
	return symbol;
}


