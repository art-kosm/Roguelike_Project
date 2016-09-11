#pragma once

#include <iostream>
#include <curses.h>

using std::string;

class Tile
{
public:
    Tile();
    Tile(const string &name, const string &type, char symbol, bool isSeen = false, bool isRemembered = false);
    virtual ~Tile();
    virtual void draw(int x, int y);
    char getSymbol();
    void setSeen(bool status);
    void setRemembered(bool status);
    const string &getName();
    const string &getType();

protected:
    string name;
    string type;
    char symbol;
    bool isSeen;
    bool isRemembered;
};

