#include "terrain.h"

Terrain::Terrain() : isPassable(true)
{}

Terrain::Terrain(const string &name, Type type, char symbol, bool isPassable)
    : Tile(name, type, symbol), isPassable(isPassable)
{}

bool Terrain::getPassability()
{
    return isPassable;
}

void Terrain::initialize(const string &name, Type type, char symbol, bool isPassable)
{
    this->name = name;
    this->type = type;
    this->symbol = symbol;
    this->isPassable = isPassable;
}

