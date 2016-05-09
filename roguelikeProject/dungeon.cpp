#include "dungeon.h"

Dungeon::Dungeon() : name("Default dungeon"), depth(5), symbol('*')
{
	for (int i = 0; i < depth; i++)
		levels.push_back(new Map());
	current = 0;
	x = 0;
	y = 0;
}

Dungeon::Dungeon(const std::string &name, int depth, char symbol, int current, int x, int y) :
	name(name), depth(depth), symbol(symbol)
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

Map *Dungeon::getLevel(int depth)
{
	return levels.at(depth);
}

void Dungeon::setLevel(int depth, Map *level)
{
	Map *temp = levels.at(depth);
	levels.at(depth + 1)->getEntranceByLeadsTo(temp)->setLeadsTo(level);
	levels.at(depth - 1)->getEntranceByLeadsTo(temp)->setLeadsTo(level);
	level->addEntrance(new Entrance(term_x / 2, term_y / 2 - 2, '>', level, levels.at(depth + 1)));
	level->addEntrance(new Entrance(term_x / 2, term_y / 2 + 2, '<', level, levels.at(depth - 1)));
	levels.at(depth) = level;
	delete temp;
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

const std::string &Dungeon::getName()
{
	return name;
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

