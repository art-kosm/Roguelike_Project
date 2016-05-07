#pragma once

#include <curses.h>
#include "map.h"

class Map;
class Entrance
{
public:
	Entrance();
	Entrance(int x, int y, char symbol, Map *leadsFrom, Map *leadsTo, bool isSeen = false, bool isRemembered = false);
	~Entrance();
	void draw();
	int getX();
	int getY();
	Map *getLeadsTo();
	Map *getLeadsFrom();
	void setSeen(bool status);

protected:
	int x;
	int y;
	char symbol;
	Map *leadsFrom;
	Map *leadsTo;
	bool isSeen;
	bool isRemembered;
};

