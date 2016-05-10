#pragma once

#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "dungeon.h"
#include "entrance.h"
#include "tile.h"
#include "terrain.h"
#include "actor.h"
#include "generalConstants.h"
#include "pathfinding.h"

using namespace generalConstants;
using std::vector;
using std::string;
using std::ifstream;

class Pathfinding;
class Dungeon;
class Entrance;
class Actor;
class Map
{
public:
	Map();
	Map(const string &filename);
	~Map();
	void draw(int indent = 0);
	void addDungeon(Dungeon *dungeon);
	void addEntrance(Entrance *entrance);
	void addActor(Actor *actor);
	void setTerrainTile(Terrain element, int x, int y);
	Terrain getTerrainTileAt(int x, int y);
	void setTileSeen(int x, int y, bool status);
	int getEntrancesNumber();
	Entrance *getEntranceOn(int x, int y);
	Entrance *getEntranceByLeadsTo(Map *leadsTo);
	Dungeon *getDungeonByName(const string &name);
	Actor *getActorOn(int x, int y);
	bool tileIsOccupied(int x, int y);
	bool tileIsPassable(int x, int y);
	void setEverythingSeen(bool status);
	void processActorsTurns(Actor *player);
	Pathfinding *getPathfinding();
	const string &getName();
	void setName(const string &name);

private:
	WINDOW *window;
	Terrain **terrain;
	vector<Dungeon *> dungeons;
	vector<Entrance *> entrances;
	vector<Actor *> actors;
	Pathfinding *pathfinding;
	string name;

	void drawTerrain(int indent = 0);
	void drawEntrances(int indent = 0);
	void drawActors(int indent = 0);
};
