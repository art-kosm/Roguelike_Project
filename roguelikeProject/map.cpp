#include "map.h"

Map::Map() : window(stdscr)
{
	terrain = new TerrainElement *[term_y];
	for (int i = 0; i < term_y; i++)
		terrain[i] = new TerrainElement[term_x];
	player = new Actor("player", '@', term_x / 2, term_y / 2, 1);
}

Map::~Map()
{
	for (int i = 0; i < term_y; i++)
		delete[] terrain[i];
	delete[] terrain;
}

void Map::draw()
{
	drawTerrain();
	//drawActors();
	mvaddch(player->getY(), player->getX(), player->getSymbol());
}

void Map::drawTerrain()
{
	for (int i = 0; i < term_y; i++)
		for (int j = 0; j < term_x; j++)
			mvaddch(i, j, terrain[i][j].getSymbol());
}

void Map::setTile(TerrainElement element)
{
	terrain[element.getX()][element.getY()] = element;
}

void Map::movePlayer(int x, int y)
{
	if (!terrain[y][x].getPassability())
		return;
	player->setX(x);
	player->setY(y);
}

Actor *Map::getPlayer()
{
	return player;
}

