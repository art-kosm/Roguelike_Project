#pragma once

#include "tile.h"
#include "actor.h"

class Item : public Tile
{
public:
	Item();
	virtual void useOn(Actor *actor) = 0;
};

