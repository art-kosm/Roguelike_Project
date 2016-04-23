#pragma once

#include <iostream>
#include "mapElement.h"

using std::string;

class Actor : public MapElement
{
public:
	Actor();
	Actor(string name, std::string type, char symbol, int x, int y, int hp);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

private:
	int hp;
	int x;
	int y;
};

