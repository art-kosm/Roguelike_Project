#include "map.h"

Map::Map() : window(stdscr)
{
    terrain = new Terrain *[map_y];
    for (int i = 0; i < map_y; i++)
        terrain[i] = new Terrain[map_x];

    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            terrain[i][j].intiialize("Stone floor", "floor", '.', true, true);

    pathfinding = new Pathfinding(this);
    name = "Some map";
}

Map::Map(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        Map();
        return;
    }

    terrain = new Terrain *[map_y];
    for (int i = 0; i < map_y; i++)
        terrain[i] = new Terrain[map_x];

    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
        {
            char ch = ' ';
            file >> ch;
            if (ch == '#')
                terrain[i][j].intiialize("Wall", "wall", '#', false, false);
            else
                terrain[i][j].intiialize("Stone floor", "floor", '.', true, true);
        }
    file.close();

    pathfinding = new Pathfinding(this);
    name = "Some map";
}

Map::~Map()
{
    for (int i = 0; i < map_y; i++)
        delete[] terrain[i];
    delete[] terrain;

    for (int i = 0; (unsigned)i < dungeons.size(); i++)
        delete dungeons.at(i);

    for (int i = 0; (unsigned)i < entrances.size(); i++)
        delete entrances.at(i);

    for (int i = 0; (unsigned)i < actors.size(); i++)
        delete actors.at(i);

    for (int i = 0; (unsigned)i < items.size(); i++)
        delete items.at(i);

    delete pathfinding;
}

void Map::draw(int indent)
{
    drawTerrain(indent);
    drawEntrances(indent);
    drawItems(indent);
    drawActors(indent);
}

void Map::drawWallsInRed(int indent)
{
    int color = 1;
    init_pair(color, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(color));
    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            if (!terrain[i][j].getPassability())
                terrain[i][j].draw(j, i + indent);
    attroff(COLOR_PAIR(color));
}

void Map::addDungeon(Dungeon *dungeon)
{
    dungeons.push_back(dungeon);
    addEntrance(new Entrance(dungeon->getX(), dungeon->getY(), dungeon->getSymbol(), this, dungeon->getFirstLevel()));
    dungeon->getFirstLevel()->addEntrance(new Entrance(map_x / 2, map_y / 2 + 2, '<', dungeon->getFirstLevel(), this));
    dungeon->connectLevels();
}

void Map::addEntrance(Entrance *entrance)
{
    for (int i = 0; (unsigned)i < entrances.size(); i++)
        if (entrances.at(i) == entrance)
            return;
    entrances.push_back(entrance);
}

void Map::addActor(Actor *actor)
{
    actors.push_back(actor);
}

void Map::addItem(Item *item)
{
    items.push_back(item);
}

void Map::drawTerrain(int indent)
{
    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            terrain[i][j].draw(j, i + indent);
}

void Map::drawEntrances(int indent)
{
    for (int i = 0; (unsigned)i < entrances.size(); i++)
        entrances.at(i)->draw(indent);
}

void Map::drawItems(int indent)
{
    for (int i = 0; (unsigned)i < items.size(); i++)
        items.at(i)->draw(indent);
}

void Map::drawActors(int indent)
{
    for (int i = 0; (unsigned)i < actors.size(); i++)
        actors.at(i)->draw(indent);
}

void Map::removeDead()
{
    for (int i = 0; (unsigned)i < actors.size(); i++)
        if (!actors.at(i)->isAlive())
            actors.erase(actors.begin() + i);
}

void Map::setTerrainTile(Terrain element, int x, int y)
{
    terrain[y][x] = element;
}

Terrain Map::getTerrainTileAt(int x, int y)
{
    return terrain[y][x];
}

void Map::setTileSeen(int x, int y, bool status)
{
    terrain[y][x].setSeen(status);
    for (int i = 0; (unsigned)i < entrances.size(); i++)
        if (entrances.at(i)->getX() == x && entrances.at(i)->getY() == y)
            entrances.at(i)->setSeen(status);
    for (int i = 0; (unsigned)i < actors.size(); i++)
        if (actors.at(i)->getX() == x && actors.at(i)->getY() == y)
            actors.at(i)->setSeen(status);
    for (int i = 0; (unsigned)i < items.size(); i++)
        if (items.at(i)->getX() == x && items.at(i)->getY() == y)
            items.at(i)->setSeen(status);
}

int Map::getEntrancesNumber()
{
    return entrances.size();
}

Entrance *Map::getEntranceOn(int x, int y)
{
    for (int i = 0; (unsigned)i < entrances.size(); i++)
        if (entrances.at(i)->getX() == x && entrances.at(i)->getY() == y)
            return entrances.at(i);
    return nullptr;
}

Entrance *Map::getEntranceByLeadsTo(Map *leadsTo)
{
    for (int i = 0; (unsigned)i < entrances.size(); i++)
        if (entrances.at(i)->getLeadsTo() == leadsTo)
            return entrances.at(i);
    return nullptr;
}

Dungeon *Map::getDungeonByName(const std::string &name)
{
    for (int i = 0; (unsigned)i < dungeons.size(); i++)
        if (dungeons.at(i)->getName() == name)
            return dungeons.at(i);
    return nullptr;
}

Actor *Map::getActorOn(int x, int y)
{
    for (int i = 0; (unsigned)i < actors.size(); i++)
        if (actors.at(i)->getX() == x && actors.at(i)->getY() == y)
            return actors.at(i);
    return nullptr;
}

bool Map::tileIsOccupied(int x, int y)
{
    for (int i = 0; (unsigned)i < actors.size(); i++)
        if (actors.at(i)->getX() == x && actors.at(i)->getY() == y)
            return true;
    return false;
}

bool Map::tileIsPassable(int x, int y)
{
    return terrain[y][x].getPassability();
}

void Map::setEverythingSeen(bool status)
{
    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            terrain[i][j].setSeen(status);
    for (int i = 0; (unsigned)i < entrances.size(); i++)
        entrances.at(i)->setSeen(status);
    for (int i = 0; (unsigned)i < actors.size(); i++)
        actors.at(i)->setSeen(status);
    for (int i = 0; (unsigned)i < items.size(); i++)
        items.at(i)->setSeen(status);
}

void Map::processActorsTurns(Actor *player)
{
    removeDead();
    for (int i = 0; (unsigned)i < actors.size(); i++)
        actors.at(i)->takeTurn(player);
}

Pathfinding *Map::getPathfinding()
{
    return pathfinding;
}

const std::string &Map::getName()
{
    return name;
}

void Map::setName(const std::string &name)
{
    this->name = name;
}

Item *Map::getItemAt(int x, int y)
{
    for (int i = 0; (unsigned)i < items.size(); i++)
        if (items.at(i)->getX() == x && items.at(i)->getY() == y)
            return items.at(i);
    return nullptr;
}

void Map::removeItem(Item *item)
{
    for (int i = 0; (unsigned)i < items.size(); i++)
        if (items.at(i) == item)
            items.erase(items.begin() + i);
}


