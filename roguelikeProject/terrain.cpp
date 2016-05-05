#include "terrain.h"

Terrain::Terrain() : isPassable(true)
{
}

Terrain::Terrain(const string &name, string type, char symbol, bool isPassable)
	: Tile(name, type, symbol), isPassable(isPassable)
{

}

bool Terrain::getPassability()
{
	return isPassable;
}

void Terrain::intiialize(const string &name, const string &type, char symbol, bool isPassable)
{
	this->name = name;
	this->type = type;
	this->symbol = symbol;
	this->isPassable = isPassable;
}

