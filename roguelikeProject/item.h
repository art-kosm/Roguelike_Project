#pragma once

#include "tile.h"

class Actor;
class Item : public Tile
{
public:
	Item(const string &name, const string &type, char symbol, bool isSeen = false, bool isRemembered = false, int x = 0, int y = 0);
	virtual void useOn(Actor *actor) = 0;
	void draw(int indent = 0);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
private:
	int x;
	int y;
};

