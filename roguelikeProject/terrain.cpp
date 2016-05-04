#include "terrain.h"

Terrain::Terrain() : isPassable(true)
{
}

Terrain::Terrain(string name, string type, char symbol, bool isPassable)
	: Tile(name, type, symbol), isPassable(isPassable)
{

}

bool Terrain::getPassability()
{
	return isPassable;
}

