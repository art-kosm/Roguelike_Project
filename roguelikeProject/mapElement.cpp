#include "mapElement.h"

MapElement::MapElement() : name ("default"), symbol('.')
{
}

MapElement::MapElement(std::string &name, char symbol) : name(name), symbol(symbol)
{
}

char MapElement::getSymbol()
{
	return symbol;
}


