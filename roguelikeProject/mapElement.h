#pragma once

#include <iostream>

using std::string;

class MapElement
{
public:
	MapElement();
	MapElement(string &name, char symbol, int x, int y);
	char getSymbol();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

protected:
	string name;
	char symbol;
	int x;
	int y;
};

