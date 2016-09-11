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
#include "item.h"
#include "terrain.h"
#include "actor.h"
#include "generalConstants.h"

using namespace generalConstants;
using std::vector;
using std::string;
using std::ifstream;
using std::pair;

class Dungeon;
class Town;
class Entrance;

class Map
{
public:
    Map(const string &filename = "");
    Map(int **generated, bool waterWalls);
    virtual ~Map();
    void draw(int indent = 0);
    void drawWallsInRed(int indent = 0);

    void addDungeon(Dungeon *dungeon);
    void addTown(Town *town, int x, int y);
    void addEntrance(Entrance *entrance);
    void addActor(Actor *actor);
    void addItem(Item *item);
    void addEnemies(int number, bool withDragons);

    void setName(const string &name);
    void setTerrainTile(Terrain element, int x, int y);
    void setTileSeen(int x, int y, bool status);
    void setEverythingSeen(bool status);

    const string &getName();
    Terrain getTerrainTileAt(int x, int y);
    int getEntrancesNumber();
    Entrance *getEntranceOn(int x, int y);
    Entrance *getEntranceByLeadsTo(Map *leadsTo);
    Dungeon *getDungeonById(int id);
    Actor *getActorOn(int x, int y);
    Item *getItemAt(int x, int y);

    bool tileIsOccupied(int x, int y);
    bool tileIsPassable(int x, int y);
    bool isWater(int x, int y);
    int processActorsTurns(Actor *player, string *message);
    void removeItem(Item *item);
    pair<int, int> findEntrancePosition();
    pair<int, int> findExitPosition();
    void flood();
    bool isEntrance(int x, int y);

protected:
    WINDOW *window;
    Terrain **terrain;
    vector<Dungeon *> dungeons;
    vector<Town *> towns;
    vector<Entrance *> entrances;
    vector<Item *> items;
    vector<Actor *> actors;
    string name;
    string dungeonNames[8] = {"Diavolic dungeon", "Angelic dungeon", "Earth dungeon", "Fire dungeon", "Water dungeon", "Air dungeon", "Strange dungeon", "Ordinary dungeon"};
    string townNames[9] = {"Cornelia", "Pravoka", "Elfheim", "Mount Duergar", "Melmond", "Crescent Lake", "Onrac", "Lufenia", "Gaia"};
    string humanoidNames[3] = {"Goblin", "Imp", "Orc"};
    string dragonNames[3] = {"Ark Dragon", "Dark Dragon", "Kaiser Dragon"};

    int flooded;

    void drawTerrain(int indent = 0);
    void drawEntrances(int indent = 0);
    void drawItems(int indent = 0);
    void drawActors(int indent = 0);

    int removeDead(string *message);
    pair<int, int> findPassableTile();
};
