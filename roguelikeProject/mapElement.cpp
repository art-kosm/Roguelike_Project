#include "mapElement.h"

MapElement::MapElement() : name ("default"), symbol('.')
{
}

MapElement::MapElement(std::string &name, std::string &type, char symbol) : name(name), type(type), symbol(symbol)
{
}

char MapElement::getSymbol()
{
	return symbol;
}


