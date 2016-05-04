#pragma once

#include "map.h"
#include "entrance.h"

using std::vector;

class Map;
class Dungeon
{
public:
	Dungeon();
	Dungeon(int depth, char symbol, int current, int x, int y);
	~Dungeon();
	Map *getFirstLevel();
	Map *getCurrentLevel();
	void draw();
	void connectLevels();
	char getSymbol();
	int getX();
	int getY();

private:
	int depth;
	char symbol;
	vector<Map *> levels;
	int current;
	int x;
	int y;
};
