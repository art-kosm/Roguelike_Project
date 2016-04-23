#pragma once

#include "map.h"

using std::vector;

class Dungeon
{
public:
	Dungeon();
	Dungeon(int depth, int current);
	Map *getCurrentLevel();
	void moveUp();
	void moveDown();

private:
	int depth;
	vector<Map *> levels;
	int current;
};
