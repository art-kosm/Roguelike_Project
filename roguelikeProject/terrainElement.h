#pragma once

#include "mapElement.h"

class TerrainElement : public MapElement
{
public:
	TerrainElement();
	TerrainElement(string name, char symbol, bool isPassable);
	bool getPassability();

private:
	bool isPassable;
};

