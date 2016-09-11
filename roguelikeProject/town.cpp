#include "town.h"
#include "citizenAI.h"
#include "traderAI.h"
#include "potion.h"

#define _USE_MATH_DEFINES
#include "math.h"

Town::Town(const std::string &name)
{
    this->name = "the town of " + name;

    terrain = new Terrain *[map_y];
    for (int i = 0; i < map_y; i++)
        terrain[i] = new Terrain[map_x];

    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            terrain[i][j].initialize("Grass", GRASS, '.', true);

    addHousesAndLakes(20, 10);
    addCitizens(20);
    addTraders(1);
}

void Town::addCitizens(int number)
{
    for (int i = 0; i < number; i++)
    {
        pair<int, int> tile = findPassableTile();

        Actor *citizen = new Actor("A citizen", CITIZEN, 'c', tile.first, tile.second, 1, 1, new CitizenAI(), this);
        addActor(citizen);
    }
}

void Town::addTraders(int number)
{
    for (int i = 0; i < number; i++)
    {
        pair<int, int> tile = {map_x / 2 + number, map_y / 2 + number};

        Actor *trader = new Actor("A trader", TRADER, 't', tile.first, tile.second, 1, 1, new TraderAI(), this);
        trader->getInventory()->addItem(new Potion());
        addActor(trader);
    }
}

void Town::addHousesAndLakes(int housesNumber, int lakesNumber)
{
    bool houseLand[map_y][map_x];
    for (int i = 0; i < map_x; i++)
        for (int j = 0; j < map_y; j++)
            houseLand[j][i] = false;

    bool door[map_y][map_x];
    for (int i = 0; i < map_x; i++)
        for (int j = 0; j < map_y; j++)
            door[j][i] = false;

    for (int i = 0; i < housesNumber; i++)
    {
        int cornerX = rand() % (map_x - 2) + 1;
        int cornerY = rand() % (map_y - 2) + 1;
        if (rand() % 2)
            door[cornerY + 1][cornerX] = true;
        else
            door[cornerY][cornerX + 1] = true;
        int sizeX = rand() % 17 + 3;
        int sizeY = rand() % 17 + 3;

        for (int i = cornerX; i < cornerX + sizeX && i < map_x - 1; i++)
            for (int j = cornerY; j < cornerY + sizeY && j < map_y - 1; j++)
                houseLand[j][i] = true;
    }

    for (int i = 1; i < map_x - 1; i++)
        for (int j = 1; j < map_y - 1; j++)
            if (houseLand[j][i])
                if (!houseLand[j - 1][i] || !houseLand[j + 1][i] ||
                    !houseLand[j][i - 1] || !houseLand[j][i + 1] ||
                    !houseLand[j - 1][i - 1] || !houseLand[j - 1][i + 1] ||
                    !houseLand[j + 1][i - 1] || !houseLand[j + 1][i + 1])
                {
                    if (!door[j][i])
                        terrain[j][i].initialize("Wall", WALL, '#', false);
                    else
                        terrain[j][i].initialize("Door", FLOOR, '/', true);
                }

    int rays = 360;
    int step = 3;
    for (int i = 0; i < lakesNumber; i++)
    {
        int x = rand() % (map_x - 2) + 1;
        int y = rand() % (map_y - 2) + 1;
        int radius = rand() % 10 + 2;

        for (int i = 0; i < rays + 1; i += step)
        {
            float dx = sin(i / (180 / M_PI));
            float dy = cos(i / (180 / M_PI));

            float temp_x = x;
            float temp_y = y;

            for (int j = 0; j < radius; j++)
            {
                temp_x += dx;
                temp_y += dy;

                if (temp_x > map_x - 1 || temp_x < 0 || temp_y > map_y - 1 || temp_y < 0)
                    break;
                if (!houseLand[(int) temp_y + 1][(int) temp_x + 1] &&
                    !houseLand[(int) temp_y + 1][(int) temp_x - 1] &&
                    !houseLand[(int) temp_y - 1][(int) temp_x + 1] &&
                    !houseLand[(int) temp_y - 1][(int) temp_x - 1])
                    terrain[(int) temp_y][(int) temp_x].initialize("Water",  WATER, '~', true);
                else
                    break;
            }
        }

        int cornerX = rand() % (map_x - 2) + 1;
        int cornerY = rand() % (map_y - 2) + 1;
        if (rand() % 2)
            door[cornerY + 1][cornerX] = true;
        else
            door[cornerY][cornerX + 1] = true;
        int sizeX = rand() % 17 + 3;
        int sizeY = rand() % 17 + 3;

        for (int i = cornerX; i < cornerX + sizeX && i < map_x - 1; i++)
            for (int j = cornerY; j < cornerY + sizeY && j < map_y - 1; j++)
                houseLand[j][i] = true;
    }
}
