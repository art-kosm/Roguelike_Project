#pragma once

#include <iostream>
#include "tile.h"
#include "generalConstants.h"
#include "map.h"
#include "AI.h"

using std::string;
using namespace generalConstants;

class AI;
class Map;
class Actor : public Tile
{
public:
	Actor();
	Actor(const string &name, const string &type, char symbol, int x, int y, int hp,
		  int perceptionRadius, AI *behaviour, Map *locatedOn = nullptr);
	void draw(int indent = 0);
	int getHP();
	int getX();
	int getY();
	int getPerceptionRadius();
	void takeTurn(Actor *player);
	void move(int x, int y);
	void setMap(Map *map);
	Map *getMap();
	void setAI(AI *behaviour);

private:
	int hp;
	int x;
	int y;
	int perceptionRadius;
	AI *behaviour;
	Map *locatedOn;
};

