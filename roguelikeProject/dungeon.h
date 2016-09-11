#pragma once

#include <iostream>
#include "map.h"
#include "entrance.h"

using std::vector;
using std::string;

class Map;
//A lot of things here are not used, should consider removing them.
class Dungeon
{
public:
    Dungeon(int id = -1, const string &name = "Default dungeon", int depth = 5, char symbol = '*', int current = 0, int x = 0, int y = 0);
    ~Dungeon();
    int getId();
    Map *getFirstLevel();
    Map *getCurrentLevel();
    Map *getLevel(int depth);
    void draw();
    void connectLevels();
    const string &getName();
    char getSymbol();
    int getX();
    int getY();

private:
    int id;
    string name;
    int depth;
    char symbol;
    vector<Map *> levels;
    int current;
    int x;
    int y;
};
