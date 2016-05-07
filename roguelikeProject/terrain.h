#pragma once

#include "tile.h"

class Terrain : public Tile
{
public:
	Terrain();
	Terrain(const string &name, string type, char symbol, bool isPassable, bool passesLight);
	bool getPassability();
	void intiialize(const string &name, const string &type, char symbol, bool isPassable, bool passesLight);

private:
	bool isPassable;
	bool passesLight;
};

