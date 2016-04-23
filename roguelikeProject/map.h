#pragma once

#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <vector>
#include "mapElement.h"
#include "terrainElement.h"
#include "actor.h"
#include "generalConstants.h"

using namespace generalConstants;
using std::vector;
using std::pair;

class Map
{
public:
	Map();
	~Map();
	void draw();
	void setTile(TerrainElement element, int x, int y);
	void movePlayer(int x, int y);
	Actor *getPlayer();
	pair<int, int> getUpExitPos();
	pair<int, int> getDownExitPos();
	bool playerIsOnUpExit();
	bool playerIsOnDownExit();

private:
	WINDOW *window;
	TerrainElement **terrain;
	Actor *player;
	pair<int, int> upExitPos;
	pair<int, int> downExitPos;

	void drawTerrain();
	void drawActors();
};
