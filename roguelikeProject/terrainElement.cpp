#include "terrainElement.h"

TerrainElement::TerrainElement() : isPassable(true)
{
}

TerrainElement::TerrainElement(std::string name, char symbol, bool isPassable)
	: MapElement(name, symbol), isPassable(isPassable)
{

}

bool TerrainElement::getPassability()
{
	return isPassable;
}

