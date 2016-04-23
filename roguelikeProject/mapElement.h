#pragma once

#include <iostream>

using std::string;

class MapElement
{
public:
	MapElement();
	MapElement(string &name, string &type, char symbol);
	char getSymbol();

protected:
	string name;
	string type;
	char symbol;
};

