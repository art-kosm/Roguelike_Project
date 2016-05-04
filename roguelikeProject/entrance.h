#pragma once

#include <curses.h>
#include "map.h"

class Map;
class Entrance
{
public:
	Entrance();
	Entrance(int x, int y, char symbol, Map *leadsFrom, Map *leadsTo);
	~Entrance();
	void draw();
	int getX();
	int getY();
	Map *getLeadsTo();
	Map *getLeadsFrom();

protected:
	int x;
	int y;
	char symbol;
	Map *leadsFrom;
	Map *leadsTo;
};

