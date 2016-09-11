#include "generalConstants.h"

#define TILE_FLOOR 0
#define TILE_WALL 1

int randomPick(int fillProbability)
{
    if (rand() % 100 < fillProbability)
        return TILE_WALL;
    else
        return TILE_FLOOR;
}

void initializeMap(int **grid, int **grid2, int fillProbability)
{
    for (int y = 1; y < map_y - 1; y++)
        for (int x = 1; x < map_x - 1; x++)
            grid[y][x] = randomPick(fillProbability);

    for (int y = 0; y < map_y; y++)
        grid[y][0] = grid[y][map_x - 1] = TILE_WALL;

    for (int x = 0; x < map_x; x++)
        grid[0][x] = grid[map_y - 1][x] = TILE_WALL;

    for (int y = 0; y < map_y; y++)
        for (int x = 0; x < map_x; x++)
            grid2[y][x] = TILE_WALL;
}

void nextGeneration(int **grid, int **grid2, int r1, int r2)
{
    for (int y = 1; y < map_y - 1; y++)
        for (int x = 1; x < map_x - 1; x++)
        {
            int adjustedR1 = 0;
            for (int i = -1; i <= 1; i++)
                for (int j = -1; j <= 1; j++)
                    if (grid[y + i][x + j] != TILE_FLOOR)
                        adjustedR1++;

            int adjustedR2 = 0;
            for (int i = y - 2; i <= y + 2; i++)
                for (int j = x - 2; j <= x + 2; j++)
                {
                    if (abs(i - y) == 2 && abs(j - x) == 2)
                        continue;
                    if (i < 0 || j < 0 || i >= map_y || j >= map_x)
                        continue;
                    if (grid[i][j] != TILE_FLOOR)
                        adjustedR2++;
                }

            if (adjustedR1 >= r1 || adjustedR2 <= r2)
                grid2[y][x] = TILE_WALL;
            else
                grid2[y][x] = TILE_FLOOR;
        }

    for (int y = 1; y < map_y - 1; y++)
        for (int x = 1; x < map_x - 1; x++)
            grid[y][x] = grid2[y][x];
}

void removeIsolatedCaves(int **grid)
{
    //selecting the central tile
    int x = map_x / 2;
    int y = map_y / 2;
    bool found = false;
    while (!found)
        //searching for the closest passable tile, moving away from the central tile
        for (int r = 0; r < map_x / 2 && r < map_y / 2 && !found; r++)
            for (int xPos = x - r; xPos <= x + r && !found; xPos++)
                if (xPos == x - r || xPos == x + r)
                {
                    for (int yPos = y - r; yPos <= y + r && !found; yPos++)
                        if (grid[yPos][xPos] == TILE_FLOOR)
                        {
                            x = xPos;
                            y = yPos;
                            found = true;
                        }
                }
                else if (grid[y - r][xPos] == TILE_FLOOR)
                {
                    x = xPos;
                    y = y - r;
                    found = true;
                }
                else if (grid[y + r][xPos] == TILE_FLOOR)
                {
                    x = xPos;
                    y = y + r;
                    found = true;
                }

    //a passable tile selected
    //flooding its neighborhood
    bool flooded[map_y][map_x];
    for (int yPos = 0; yPos < map_y; yPos++)
        for (int xPos = 0; xPos < map_x; xPos++)
            flooded[yPos][xPos] = false;
    flooded[y][x] = true;
    bool unfloodedLeft = true;
    while (unfloodedLeft)
    {
        unfloodedLeft = false;
        for (int xPos = 1; xPos < map_x; xPos++)
            for (int yPos = 1; yPos < map_y; yPos++)
                if (flooded[yPos][xPos])
                {
                    if (grid[yPos + 1][xPos] == TILE_FLOOR && !flooded[yPos + 1][xPos])
                    {
                        flooded[yPos + 1][xPos] = true;
                        unfloodedLeft = true;
                    }
                    if (grid[yPos - 1][xPos] == TILE_FLOOR && !flooded[yPos - 1][xPos])
                    {
                        flooded[yPos - 1][xPos] = true;
                        unfloodedLeft = true;
                    }
                    if (grid[yPos][xPos + 1] == TILE_FLOOR && !flooded[yPos][xPos + 1])
                    {
                        flooded[yPos][xPos + 1] = true;
                        unfloodedLeft = true;
                    }
                    if (grid[yPos][xPos - 1] == TILE_FLOOR && !flooded[yPos][xPos - 1])
                    {
                        flooded[yPos][xPos - 1] = true;
                        unfloodedLeft = true;
                    }
                }
    }

    //some cave is flooded
    //transforming the other caves into pure walls
    for (int xPos = 0; xPos < map_x; xPos++)
        for (int yPos = 0; yPos < map_y; yPos++)
            if (grid[yPos][xPos] == TILE_FLOOR && !flooded[yPos][xPos])
                grid[yPos][xPos] = TILE_WALL;
}

int **generate()
{
    const int generations = 2;

    const int r1[generations] = {5, 5};
    const int r2[generations] = {2, -1};
    const int repetitions[generations] = {4, 3};

    int **grid = new int*[map_y];
    for (int y = 0; y < map_y; y++)
        grid[y] = new int[map_x];

    int **grid2 = new int*[map_y];
    for (int y = 0; y < map_y; y++)
        grid2[y] = new int[map_x];

    const int fillProbability = 40;
    initializeMap(grid, grid2, fillProbability);

    for (int i = 0; i < generations; i++)
        for (int j = 0; j < repetitions[i]; j++)
            nextGeneration(grid, grid2, r1[i], r2[i]);

    removeIsolatedCaves(grid);

    return grid;
}
