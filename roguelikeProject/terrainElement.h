#pragma once

#include "mapElement.h"

class TerrainElement : public MapElement
{
public:
	TerrainElement();
	TerrainElement(string name, char symbol, int x, int y, bool isPassable);
	bool getPassability();

private:
	bool isPassable;
};

