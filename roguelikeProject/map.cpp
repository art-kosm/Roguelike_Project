#include <limits>
#include "map.h"
#include "town.h"
#include "aggressiveAI.h"

Map::Map(const string &filename) : window(stdscr), name("Some map"), flooded(map_x)
{
    terrain = new Terrain *[map_y];
    for (int i = 0; i < map_y; i++)
        terrain[i] = new Terrain[map_x];

    ifstream file(filename);

    if (file.is_open())
    {
        int id = 0;

        for (int i = 0; i < map_y; i++)
            for (int j = 0; j < map_x; j++)
            {
                char ch = ' ';
                file >> ch;
                switch (ch)
                {
                case '.':
                    terrain[i][j].initialize("Grass", GRASS, '.', true);
                    break;

                case '#':
                    terrain[i][j].initialize("Wall", WALL, '#', false);
                    break;

                case '*':
                {
                    int num = rand() % 8;
                    while (dungeonNames[num] == "")
                        num = rand() % 8;
                    addDungeon(new Dungeon(id, dungeonNames[num], 9, '*', 0, j, i));
                    dungeonNames[num] = "";
                    id++;
                } break;

                case '~':
                    terrain[i][j].initialize("Water",  WATER, '~', true);
                    break;

                case 'O':
                {
                    int num = rand() % 9;
                    while (townNames[num] == "")
                        num = rand() % 9;
                    addTown(new Town(townNames[num]), j, i);
                    townNames[num] = "";
                    id++;
                } break;

                default:
                    terrain[i][j].initialize("Stone floor", FLOOR, '.', true);
                    break;
                }
            }
        file.close();
    }
    else
        for (int i = 0; i < map_y; i++)
            for (int j = 0; j < map_x; j++)
                terrain[i][j].initialize("Stone floor", FLOOR, '.', true);
}

Map::Map(int **generated, bool waterWalls) : name("Some map"), flooded(map_x)
{
    terrain = new Terrain *[map_y];
    for (int i = 0; i < map_y; i++)
        terrain[i] = new Terrain[map_x];

    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            if (generated[i][j] == 0)
                terrain[i][j].initialize("Stone floor", FLOOR, '.', true);
            else if (waterWalls)
                terrain[i][j].initialize("Water",  WATER, '~', true);
            else
                terrain[i][j].initialize("Wall", WALL, '#', false);
}

Map::~Map()
{
    for (int i = 0; i < map_y; i++)
        delete[] terrain[i];
    delete[] terrain;

    for (int i = 0; (unsigned) i < dungeons.size(); i++)
        delete dungeons.at(i);

    for (int i = 0; (unsigned) i < towns.size(); i++)
        delete towns.at(i);

    for (int i = 0; (unsigned) i < entrances.size(); i++)
        delete entrances.at(i);

    for (int i = 0; (unsigned) i < actors.size(); i++)
        delete actors.at(i);

    for (int i = 0; (unsigned) i < items.size(); i++)
        delete items.at(i);
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
    attron(COLOR_PAIR(3));
    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            if (!terrain[i][j].getPassability())
                terrain[i][j].draw(j, i + indent);
    attroff(COLOR_PAIR(3));
}

void Map::addDungeon(Dungeon *dungeon)
{
    dungeons.push_back(dungeon);

    Map *dungeonFirstLevel = dungeon->getFirstLevel();
    addEntrance(new Entrance(dungeon->getX(), dungeon->getY(), dungeon->getSymbol(), this, dungeonFirstLevel));

    pair<int, int> exit = dungeonFirstLevel->findExitPosition();
    dungeonFirstLevel->addEntrance(new Entrance(exit.first, exit.second, '<', dungeonFirstLevel, this));

    dungeon->connectLevels();
}

void Map::addTown(Town *town, int x, int y)
{
    towns.push_back(town);

    addEntrance(new Entrance(x, y, 'O', this, town));
    town->addEntrance(new Entrance(0, town->findExitPosition().second, '<', town, this));
}

void Map::addEntrance(Entrance *entrance)
{
    for (int i = 0; (unsigned) i < entrances.size(); i++)
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
    for (int i = 0; (unsigned) i < entrances.size(); i++)
        entrances.at(i)->draw(indent);
}

void Map::drawItems(int indent)
{
    for (int i = 0; (unsigned) i < items.size(); i++)
        items.at(i)->draw(indent);
}

void Map::drawActors(int indent)
{
    for (int i = 0; (unsigned) i < actors.size(); i++)
        actors.at(i)->draw(indent);
}

int Map::removeDead(string *message)
{
    int points = 0;

    for (int i = 0; (unsigned) i < actors.size(); i++)
    {
        Actor *actor = actors.at(i);
        if (!actor->isAlive())
        {
            if (actor->getType() != PLAYER)
                *message += actor->getName() + " defeated! ";

            vector<Item *> inventory = actor->getInventory()->getItems();
            for (int i = 0; (unsigned) i < inventory.size(); i++)
            {
                Item *item = inventory.at(i);
                item->setX(actor->getX());
                item->setY(actor->getY());
                addItem(item);
            }

            actors.erase(actors.begin() + i);
            points += 1;
        }
    }

    return points;
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
    for (int i = 0; (unsigned) i < entrances.size(); i++)
        if (entrances.at(i)->getX() == x && entrances.at(i)->getY() == y)
            entrances.at(i)->setSeen(status);
    for (int i = 0; (unsigned) i < actors.size(); i++)
        if (actors.at(i)->getX() == x && actors.at(i)->getY() == y)
            actors.at(i)->setSeen(status);
    for (int i = 0; (unsigned) i < items.size(); i++)
        if (items.at(i)->getX() == x && items.at(i)->getY() == y)
            items.at(i)->setSeen(status);
}

int Map::getEntrancesNumber()
{
    return entrances.size();
}

Entrance *Map::getEntranceOn(int x, int y)
{
    for (int i = 0; (unsigned) i < entrances.size(); i++)
        if (entrances.at(i)->getX() == x && entrances.at(i)->getY() == y)
            return entrances.at(i);
    return nullptr;
}

Entrance *Map::getEntranceByLeadsTo(Map *leadsTo)
{
    for (int i = 0; (unsigned) i < entrances.size(); i++)
        if (entrances.at(i)->getLeadsTo() == leadsTo)
            return entrances.at(i);
    return nullptr;
}

Dungeon *Map::getDungeonById(int id)
{
    for (int i = 0; (unsigned) i < dungeons.size(); i++)
        if (dungeons.at(i)->getId() == id)
            return dungeons.at(i);
    return nullptr;
}

Actor *Map::getActorOn(int x, int y)
{
    for (int i = 0; (unsigned) i < actors.size(); i++)
    {
        Actor *actor = actors.at(i);
        if (actor->getX() == x && actor->getY() == y)
            return actor;
    }
    return nullptr;
}

bool Map::tileIsOccupied(int x, int y)
{
    for (int i = 0; (unsigned) i < actors.size(); i++)
        if (actors.at(i)->getX() == x && actors.at(i)->getY() == y)
            return true;
    return false;
}

bool Map::tileIsPassable(int x, int y)
{
    return terrain[y][x].getPassability();
}

bool Map::isWater(int x, int y)
{
    return terrain[y][x].getType() == WATER;
}

void Map::setEverythingSeen(bool status)
{
    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            terrain[i][j].setSeen(status);
    for (int i = 0; (unsigned) i < entrances.size(); i++)
        entrances.at(i)->setSeen(status);
    for (int i = 0; (unsigned) i < actors.size(); i++)
        actors.at(i)->setSeen(status);
    for (int i = 0; (unsigned) i < items.size(); i++)
        items.at(i)->setSeen(status);
}

int Map::processActorsTurns(Actor *player, string *message)
{
    if (flooded < map_x && flooded >= 0)
    {
        for (int i = 0; i < map_y; i++)
        {
            terrain[i][flooded].initialize("Water",  WATER, '~', true);
            Actor *actor = getActorOn(flooded, i);
            if (actor != nullptr)
                actor->takeDamage(std::numeric_limits<int>::max());
        }
        flooded--;
    }

    int collectedPoints = removeDead(message);
    for (int i = 0; (unsigned) i < actors.size(); i++)
        actors.at(i)->takeTurn(player);

    return collectedPoints;
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
    for (int i = 0; (unsigned) i < items.size(); i++)
        if (items.at(i)->getX() == x && items.at(i)->getY() == y)
            return items.at(i);
    return nullptr;
}

void Map::removeItem(Item *item)
{
    for (int i = 0; (unsigned) i < items.size(); i++)
        if (items.at(i) == item)
            items.erase(items.begin() + i);
}

pair<int, int> Map::findEntrancePosition()
{
    for (int i = map_x + map_y - 1; i >= 0; i--)
        for (int x = 0; x <= i; x++)
            if (x < map_x && i - x < map_y)
                if (tileIsPassable(x, i - x) && !isWater(x, i - x))
                    return {x, i - x};
    return {0, 0};
}

pair<int, int> Map::findExitPosition()
{
    for (int i = 0; i < map_x + map_y; i++)
        for (int x = 0; x <= i; x++)
            if (x < map_x && i - x < map_y)
                if (tileIsPassable(x, i - x) && !isWater(x, i - x))
                    return {x, i - x};
    return {0, 0};
}

void Map::addEnemies(int number, bool withDragons)
{
    int humanoids = 0;
    int dragons = 0;

    if (withDragons)
    {
        humanoids = number / 2;
        dragons = number / 2;
    }
    else
        humanoids = number;

    for (int i = 0; i < humanoids; i++)
    {
        pair<int, int> tile = findPassableTile();

        int x = tile.first;
        int y = tile.second;

        string enemyName = humanoidNames[rand() % 3];
        char enemyLetter = tolower(enemyName.at(0));
        int enemyHp = rand() % 3 + 9;
        int enemyPerception = rand() % 2 + 4;

        Actor *enemy = new Actor(enemyName, HUMANOID, enemyLetter, x, y, enemyHp,
                                 enemyPerception, new AggressiveAI(), this);
        Weapon *enemyWeapon = new Weapon("ENEMY SPEAR", rand() % 2 + 2);
        enemy->getInventory()->addItem(enemyWeapon);
        enemy->getInventory()->equipWeapon(enemyWeapon);
        addActor(enemy);
    }

    for (int i = 0; i < dragons; i++)
    {
        pair<int, int> tile = findPassableTile();

        int x = tile.first;
        int y = tile.second;

        string enemyName = dragonNames[rand() % 3];
        char enemyLetter = tolower(enemyName.at(0));
        int enemyHp = rand() % 3 + 15;
        int enemyPerception = rand() % 3 + 6;

        Actor *enemy = new Actor(enemyName, DRAGON, enemyLetter, x, y, enemyHp,
                                 enemyPerception, new AggressiveAI(), this);
        Weapon *enemyWeapon = new Weapon("POISONED CLAW", rand() % 2 + 5);
        enemy->getInventory()->addItem(enemyWeapon);
        enemy->getInventory()->equipWeapon(enemyWeapon);
        addActor(enemy);
    }
}

pair<int, int> Map::findPassableTile()
{
    int x = rand() % (map_x - 1);
    int y = rand() % (map_y - 1);

    while (!tileIsPassable(x, y) || isWater(x, y))
    {
        if (x < map_x - 1)
            x++;
        else if (y < map_y - 1)
        {
            x = 0;
            y++;
        }
        else
            x = y = 0;
    }

    return {x, y};
}

void Map::flood()
{
    flooded--;
}

bool Map::isEntrance(int x, int y)
{
    int size = entrances.size();
    for (int i = 0; i < size; i++)
        if (entrances.at(i)->getX() == x && entrances.at(i)->getY() == y)
            return true;
    return false;
}
