#pragma once

#include <curses.h>
#include <vector>
#include "mapElement.h"
#include "terrainElement.h"
#include "actor.h"
#include "generalConstants.h"

using namespace generalConstants;
using std::vector;

class Map
{
public:
	Map();
	~Map();
	void draw();
	void drawTerrain();
	void drawActors();
	void setTile(TerrainElement element, int x, int y);
	void movePlayer(int x, int y);
	Actor *getPlayer();

private:
	WINDOW *window;
	TerrainElement **terrain;
	Actor *player;
};
