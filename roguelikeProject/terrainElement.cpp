#include "terrainElement.h"

TerrainElement::TerrainElement() : isPassable(true)
{
}

TerrainElement::TerrainElement(string name, string type, char symbol, bool isPassable)
	: MapElement(name, type, symbol), isPassable(isPassable)
{

}

bool TerrainElement::getPassability()
{
	return isPassable;
}

