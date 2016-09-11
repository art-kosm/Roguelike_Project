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
    Dungeon();
    Dungeon(const string &name, int depth, char symbol, int current, int x, int y);
    ~Dungeon();
    Map *getFirstLevel();
    Map *getCurrentLevel();
    Map *getLevel(int depth);
    //Doesn't work on first one now
    void setLevel(int depth, Map *level);
    void draw();
    void connectLevels();
    const string &getName();
    char getSymbol();
    int getX();
    int getY();

private:
    string name;
    int depth;
    char symbol;
    vector<Map *> levels;
    int current;
    int x;
    int y;
};
