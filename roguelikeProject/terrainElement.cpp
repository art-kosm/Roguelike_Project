#include "terrainElement.h"

TerrainElement::TerrainElement() : isPassable(true)
{
}

TerrainElement::TerrainElement(std::string name, char symbol, int x, int y, bool isPassable)
	: MapElement(name, symbol, x ,y), isPassable(isPassable)
{

}

bool TerrainElement::getPassability()
{
	return isPassable;
}

