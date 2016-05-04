#pragma once

#include "tile.h"

class Terrain : public Tile
{
public:
	Terrain();
	Terrain(string name, string type, char symbol, bool isPassable);
	bool getPassability();

private:
	bool isPassable;
};

