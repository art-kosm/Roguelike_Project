#pragma once

#include "tile.h"

class Terrain : public Tile
{
public:
	Terrain();
	Terrain(const string &name, string type, char symbol, bool isPassable);
	bool getPassability();
	void intiialize(const string &name, const string &type, char symbol, bool isPassable);

private:
	bool isPassable;
};

