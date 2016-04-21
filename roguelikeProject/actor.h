#pragma once

#include <iostream>
#include "mapElement.h"

using std::string;

class Actor : public MapElement
{
public:
	Actor();
	Actor(string name, char symbol, int x, int y, int hp);

private:
	int hp;
};

