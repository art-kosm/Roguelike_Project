#include "dungeon.h"

Dungeon::Dungeon() : depth(5), symbol('*')
{
	for (int i = 0; i < depth; i++)
		levels.push_back(new Map());
	current = 0;
	x = 0;
	y = 0;
}

Dungeon::Dungeon(int depth, char symbol, int current, int x, int y) : depth(depth), symbol(symbol)
{
	for (int i = 0; i < depth; i++)
		levels.push_back(new Map());
	this->current = current;
	this->x = x;
	this->y = y;
}

Dungeon::~Dungeon()
{
	for (int i = 0; i < depth; i++)
		delete levels.at(i);
}

Map *Dungeon::getFirstLevel()
{
	return levels.front();
}

Map *Dungeon::getCurrentLevel()
{
	return levels.at(current);
}

void Dungeon::draw()
{
	mvaddch(y, x, symbol);
}

void Dungeon::connectLevels()
{
	for (int i = 0; i < depth - 1; i++)
	{
		Map *level = levels.at(i);
		Map *nextLevel = levels.at(i + 1);
		level->addEntrance(new Entrance(term_x / 2, term_y / 2 - 2, '>', level, nextLevel));
		nextLevel->addEntrance(new Entrance(term_x / 2, term_y / 2 + 2, '<', nextLevel, level));
	}
}

char Dungeon::getSymbol()
{
	return symbol;
}

int Dungeon::getX()
{
	return x;
}

int Dungeon::getY()
{
	return y;
}

