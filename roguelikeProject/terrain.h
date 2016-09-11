#pragma once

#include "tile.h"

class Terrain : public Tile
{
public:
    Terrain();
    Terrain(const string &name, Type type, char symbol, bool isPassable);
    bool getPassability();
    void initialize(const string &name, Type type, char symbol, bool isPassable);

private:
    bool isPassable;
};

