#include "terrain.h"

Terrain::Terrain() : isPassable(true), passesLight(true)
{
}

Terrain::Terrain(const string &name, string type, char symbol, bool isPassable, bool passesLight)
    : Tile(name, type, symbol), isPassable(isPassable), passesLight(passesLight)
{

}

bool Terrain::getPassability()
{
    return isPassable;
}

void Terrain::intiialize(const string &name, const string &type, char symbol, bool isPassable, bool passesLight)
{
    this->name = name;
    this->type = type;
    this->symbol = symbol;
    this->isPassable = isPassable;
    this->passesLight = passesLight;
}

