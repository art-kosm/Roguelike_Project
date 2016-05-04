#pragma once

#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <vector>

#include "dungeon.h"
#include "entrance.h"
#include "tile.h"
#include "terrain.h"
#include "actor.h"
#include "generalConstants.h"

using namespace generalConstants;
using std::vector;
using std::pair;

class Dungeon;
class Entrance;
class Map
{
public:
	Map();
	~Map();
	void draw();
	void addDungeon(Dungeon *dungeon);
	void addEntrance(Entrance *entrance);
	void setTerrainTile(Terrain element, int x, int y);
	int getEntrancesNumber();
	Entrance *getEntranceOn(int x, int y);
	Entrance *getEntranceByLeadsTo(Map *leadsTo);

private:
	WINDOW *window;
	Terrain **terrain;
	vector<Dungeon *> dungeons;
	vector<Entrance *> entrances;

	void drawTerrain();
	void drawEntrances();
	void drawActors();
};
