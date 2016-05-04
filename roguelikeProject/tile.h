#pragma once

#include <iostream>
#include <curses.h>

using std::string;

class Tile
{
public:
	Tile();
	Tile(const string &name, const string &type, char symbol);
	virtual ~Tile();
	virtual void draw(int x, int y);
	char getSymbol();

protected:
	string name;
	string type;
	char symbol;
};

