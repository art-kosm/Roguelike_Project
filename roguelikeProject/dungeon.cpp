#include "dungeon.h"
#include "cellularAutomataGenerator.h"
#include "gradalis.h"

Dungeon::Dungeon(int id, const std::string &name, int depth, char symbol, int current, int x, int y) :
    id(id), name(name), depth(depth), symbol(symbol), current(current), x(x), y(y)
{
    for (int i = 0; i < depth - 1; i++)
    {
        Map *level = new Map(generate(), (i + 1) % 4 == 0);
        level->setName(name + ", level " + std::to_string(i + 1));
        level->addEnemies((i + 1) * 10, i > 3);
        levels.push_back(level);
    }

    Map *lastLevel = new Map();
    lastLevel->setName(name + ", level " + std::to_string(depth));
    lastLevel->addItem(new Gradalis("GRADALIS", map_x / 2, map_y / 2));
    levels.push_back(lastLevel);
}

Dungeon::~Dungeon()
{
    for (int i = 0; i < depth; i++)
        delete levels.at(i);
}

int Dungeon::getId()
{
    return id;
}

Map *Dungeon::getFirstLevel()
{
    return levels.front();
}

Map *Dungeon::getCurrentLevel()
{
    return levels.at(current);
}

Map *Dungeon::getLevel(int depth)
{
    return levels.at(depth);
}

void Dungeon::draw()
{
    mvaddch(y, x, symbol);
}

void Dungeon::connectLevels()
{
    for (int i = 0; i < depth - 1; i++)
    {
        Map *level = levels.at(i);
        Map *nextLevel = levels.at(i + 1);

        pair<int, int> entrance = level->findEntrancePosition();
        level->addEntrance(new Entrance(entrance.first, entrance.second, '>', level, nextLevel));

        pair<int, int> exit = nextLevel->findExitPosition();
        nextLevel->addEntrance(new Entrance(exit.first, exit.second, '<', nextLevel, level));
    }
}

const std::string &Dungeon::getName()
{
    return name;
}

char Dungeon::getSymbol()
{
    return symbol;
}

int Dungeon::getX()
{
    return x;
}

int Dungeon::getY()
{
    return y;
}

