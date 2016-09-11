#pragma once

#include "tile.h"

class Terrain : public Tile
{
public:
    Terrain();
    Terrain(const string &name, Type type, char symbol, bool isPassable/*, bool passesLight*/);
    bool getPassability();
    void initialize(const string &name, Type type, char symbol, bool isPassable/*, bool passesLight*/);

private:
    bool isPassable;
    //bool passesLight;
};

