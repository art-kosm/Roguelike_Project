#include "mapElement.h"

MapElement::MapElement() : name ("default"), symbol('.'), x(0), y(0)
{
}

MapElement::MapElement(std::string &name, char symbol, int x, int y) : name(name), symbol(symbol), x(x), y(y)
{
}

char MapElement::getSymbol()
{
	return symbol;
}

int MapElement::getX()
{
	return x;
}

int MapElement::getY()
{
	return y;
}

void MapElement::setX(int x)
{
	this->x = x;
}

void MapElement::setY(int y)
{
	this->y = y;
}

