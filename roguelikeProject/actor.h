#pragma once

#include <iostream>
#include "tile.h"
#include "generalConstants.h"
#include "map.h"

using std::string;
using namespace generalConstants;

class Map;
class Actor : public Tile
{
public:
	Actor();
	Actor(const string &name, const string &type, char symbol, int x, int y, int hp,
		  int perceptionRadius, Map *locatedOn = nullptr);
	void draw();
	int getX();
	int getY();
	int getPerceptionRadius();
	void move(int x, int y);
	void setMap(Map *map);

private:
	int hp;
	int x;
	int y;
	int perceptionRadius;
	Map *locatedOn;
};

