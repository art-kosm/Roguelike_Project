#pragma once

#include <iostream>
#include "tile.h"
#include "generalConstants.h"

using std::string;
using namespace generalConstants;

class Actor : public Tile
{
public:
	Actor();
	Actor(const string &name, const string &type, char symbol, int x, int y, int hp);
	void draw();
	int getX();
	int getY();
	void move(int x, int y);

private:
	int hp;
	int x;
	int y;
};

