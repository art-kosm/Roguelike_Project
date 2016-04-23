#include "map.h"

Map::Map() : window(stdscr)
{
	terrain = new TerrainElement *[term_y];
	for (int i = 0; i < term_y; i++)
		terrain[i] = new TerrainElement[term_x];

	//srand(time(1));
	downExitPos = pair<int, int>(term_x / 2 - 2, term_y / 2 - 2);
	upExitPos = pair<int, int>(term_x / 2 + 2, term_y / 2 + 2);
	setTile(TerrainElement("exit_up", "exit_up", '<', true), upExitPos.first, upExitPos.second);
	setTile(TerrainElement("exit_down", "exit_down", '>', true), downExitPos.first, downExitPos.second);

	player = new Actor("player's name", "player", '@', term_x / 2, term_y / 2, 1);
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

bool Map::playerIsOnUpExit()
{
	return player->getX() == upExitPos.first && player->getY() == upExitPos.second;
}

bool Map::playerIsOnDownExit()
{
	return player->getX() == downExitPos.first && player->getY() == downExitPos.second;
}

void Map::setTile(TerrainElement element, int x, int y)
{
	terrain[y][x] = element;
}

void Map::movePlayer(int x, int y)
{
	if (x > term_x - 1 || y > term_y - 1|| x < 0 || y < 0)
		return;
	if (!terrain[y][x].getPassability())
		return;

	player->setX(x);
	player->setY(y);
}

Actor *Map::getPlayer()
{
	return player;
}

pair<int, int> Map::getUpExitPos()
{
	return upExitPos;
}

pair<int, int> Map::getDownExitPos()
{
	return downExitPos;
}


