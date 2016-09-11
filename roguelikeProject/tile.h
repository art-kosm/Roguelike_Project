#pragma once

#include <iostream>
#include <curses.h>

enum Type
{
    FLOOR,
    WALL,
    GRASS,
    WEAPON,
    ARMOR,
    GRADALIS,
    POTION,
    PLAYER,
    CITIZEN,
    TRADER,
    HUMANOID,
    DRAGON,
    WATER
};

using std::string;

class Tile
{
public:
    Tile();
    Tile(const string &name, Type type, char symbol, bool isSeen = false, bool isRemembered = false);
    virtual ~Tile();
    virtual void draw(int x, int y);
    char getSymbol();
    void setSeen(bool status);
    void setRemembered(bool status);
    const string &getName();
    Type getType();

protected:
    string name;
    Type type;
    char symbol;
    bool isSeen;
    bool isRemembered;
};

