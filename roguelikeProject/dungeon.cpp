#include "dungeon.h"

Dungeon::Dungeon() : depth(5)
{
	for (int i = 0; i < depth; i++)
		levels.push_back(new Map());
	current = 0;
}

Dungeon::Dungeon(int depth, int current) : depth(depth)
{
	for (int i = 0; i < depth; i++)
		levels.push_back(new Map());
	this->current = current;
}

Dungeon::~Dungeon()
{
	for (int i = 0; i < depth; i++)
		delete levels.at(i);
}

Map *Dungeon::getCurrentLevel()
{
	return levels.at(current);
}

void Dungeon::moveUp()
{
	Map *level = getCurrentLevel();
	if (level->playerIsOnUpExit() && current != 0)
	{
		current--;
		level = getCurrentLevel();
		level->movePlayer(level->getDownExitPos().first, level->getDownExitPos().second);
	}
}

void Dungeon::moveDown()
{
	Map *level = getCurrentLevel();
	if (level->playerIsOnDownExit() && current != depth - 1)
	{
		current++;
		level = getCurrentLevel();
		level->movePlayer(level->getUpExitPos().first, level->getUpExitPos().second);
	}
}

