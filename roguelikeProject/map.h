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
	void addActor(Actor *actor);
	void setTerrainTile(Terrain element, int x, int y);
	int getEntrancesNumber();
	Entrance *getEntranceOn(int x, int y);
	Entrance *getEntranceByLeadsTo(Map *leadsTo);
	Dungeon *getDungeonByName(const string &name);

private:
	WINDOW *window;
	Terrain **terrain;
	vector<Dungeon *> dungeons;
	vector<Entrance *> entrances;
	vector<Actor *> actors;

	void drawTerrain();
	void drawEntrances();
	void drawActors();
};
