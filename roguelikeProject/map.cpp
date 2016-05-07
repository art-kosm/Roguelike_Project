#include "map.h"

Map::Map() : window(stdscr)
{
	terrain = new Terrain *[term_y];
	for (int i = 0; i < term_y; i++)
		terrain[i] = new Terrain[term_x];

	for (int i = 0; i < term_y; i++)
		for (int j = 0; j < term_x; j++)
			terrain[i][j].intiialize("Stone floor", "floor", '.', true, true);
}

Map::~Map()
{
	for (int i = 0; i < term_y; i++)
		delete[] terrain[i];
	delete[] terrain;

	for (int i = 0; (unsigned)i < dungeons.size(); i++)
		delete dungeons.at(i);

	for (int i = 0; (unsigned)i < entrances.size(); i++)
		delete entrances.at(i);

	for (int i = 0; (unsigned)i < actors.size(); i++)
		delete actors.at(i);
}

void Map::draw()
{
	drawTerrain();
	drawEntrances();
	drawActors();
}

void Map::addDungeon(Dungeon *dungeon)
{
	dungeons.push_back(dungeon);
	addEntrance(new Entrance(dungeon->getX(), dungeon->getY(), dungeon->getSymbol(), this, dungeon->getFirstLevel()));
	dungeon->getFirstLevel()->addEntrance(new Entrance(term_x / 2, term_y / 2 + 2, '<', dungeon->getFirstLevel(), this));
	dungeon->connectLevels();
}

void Map::addEntrance(Entrance *entrance)
{
	entrances.push_back(entrance);
}

void Map::addActor(Actor *actor)
{
	actors.push_back(actor);
}

void Map::drawTerrain()
{
	for (int i = 0; i < term_y; i++)
		for (int j = 0; j < term_x; j++)
			terrain[i][j].draw(j, i);
}

void Map::drawEntrances()
{
	for (int i = 0; (unsigned)i < entrances.size(); i++)
		entrances.at(i)->draw();
}

void Map::drawActors()
{
	for (int i = 0; (unsigned)i < actors.size(); i++)
		actors.at(i)->draw();
}

void Map::setTerrainTile(Terrain element, int x, int y)
{
	terrain[y][x] = element;
}

Terrain Map::getTerrainTileAt(int x, int y)
{
	return terrain[y][x];
}

void Map::setTileSeen(int x, int y, bool status)
{
	terrain[y][x].setSeen(status);
	for (int i = 0; (unsigned)i < entrances.size(); i++)
		if (entrances.at(i)->getX() == x && entrances.at(i)->getY() == y)
			entrances.at(i)->setSeen(status);
	for (int i = 0; (unsigned)i < actors.size(); i++)
		if (actors.at(i)->getX() == x && actors.at(i)->getY() == y)
			actors.at(i)->setSeen(status);
}

int Map::getEntrancesNumber()
{
	return entrances.size();
}

Entrance *Map::getEntranceOn(int x, int y)
{
	for (int i = 0; (unsigned)i < entrances.size(); i++)
		if (entrances.at(i)->getX() == x && entrances.at(i)->getY() == y)
			return entrances.at(i);
	return nullptr;
}

Entrance *Map::getEntranceByLeadsTo(Map *leadsTo)
{
	for (int i = 0; (unsigned)i < entrances.size(); i++)
		if (entrances.at(i)->getLeadsTo() == leadsTo)
			return entrances.at(i);
	return nullptr;
}

Dungeon *Map::getDungeonByName(const std::string &name)
{
	for (int i = 0; (unsigned)i < dungeons.size(); i++)
		if (dungeons.at(i)->getName() == name)
			return dungeons.at(i);
	return nullptr;
}

Actor *Map::getActorOn(int x, int y)
{
	for (int i = 0; (unsigned)i < actors.size(); i++)
		if (actors.at(i)->getX() == x && actors.at(i)->getY() == y)
			return actors.at(i);
	return nullptr;
}

bool Map::tileIsOccupied(int x, int y)
{
	for (int i = 0; (unsigned)i < actors.size(); i++)
		if (actors.at(i)->getX() == x && actors.at(i)->getY() == y)
			return true;
	return false;
}

bool Map::tileIsPassable(int x, int y)
{
	return terrain[y][x].getPassability();
}

void Map::setEverythingSeen(bool status)
{
	for (int i = 0; i < term_y; i++)
		for (int j = 0; j < term_x; j++)
			terrain[i][j].setSeen(status);
	for (int i = 0; (unsigned)i < entrances.size(); i++)
		entrances.at(i)->setSeen(status);
	for (int i = 0; (unsigned)i < actors.size(); i++)
		actors.at(i)->setSeen(status);
}


