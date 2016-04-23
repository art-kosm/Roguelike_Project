#pragma once

#include <iostream>

using std::string;

class MapElement
{
public:
	MapElement();
	MapElement(string &name, char symbol);
	char getSymbol();

protected:
	string name;
	char symbol;
};

