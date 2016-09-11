#include "pathfinding.h"

Pathfinding::Pathfinding(Map *map)
{
    dijkstraMap = new float *[map_y];
    for (int i = 0; i < map_y; i++)
        dijkstraMap[i] = new float[map_x];

    inversedDijkstraMap = new float *[map_y];
    for (int i = 0; i < map_y; i++)
        inversedDijkstraMap[i] = new float[map_x];

    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            dijkstraMap[i][j] = INT_MAX;

    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            inversedDijkstraMap[i][j] = INT_MAX;

    this->map = map;
}

Pathfinding::~Pathfinding()
{
    for (int i = 0; i < map_y; i++)
        delete[] dijkstraMap[i];
    delete[] dijkstraMap;

    for (int i = 0; i < map_y; i++)
        delete[] inversedDijkstraMap[i];
    delete[] inversedDijkstraMap;
}

pair<int, int> Pathfinding::nextStepTowards(int start_x, int start_y, int destination_x, int destination_y)
{
    if (dijkstraMap[destination_y][destination_x] != 0)
        calculateDijkstraMap(destination_x, destination_y, dijkstraMap);

    return minNeighborPos(start_x, start_y);
}

pair<int, int> Pathfinding::nextStepAway(int start_x, int start_y, int destination_x, int destination_y)
{
    if (inversedDijkstraMap[destination_y][destination_x] != 0)
        calculateInversedDijkstraMap(destination_x, destination_y);

    return maxNeighborPos(start_x, start_y);
}

int Pathfinding::getDistance(int x1, int y1, int x2, int y2)
{
    if (dijkstraMap[y2][x2] != 0)
        calculateDijkstraMap(x2, y2, dijkstraMap);
    int distance = dijkstraMap[y1][x1];
    return distance;
}

void Pathfinding::calculateDijkstraMap(int destination_x, int destination_y, float **dijkstraMap)
{
    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            dijkstraMap[i][j] = INT_MAX;
    dijkstraMap[destination_y][destination_x] = 0;

    bool changed = true;
    while (changed)
    {
        changed = false;
        for (int i = 0; i < map_y; i++)
            for (int j = 0; j < map_x; j++)
                if (map->getTerrainTileAt(j, i).getPassability() &&
                        dijkstraMap[i][j] - dijkstraMap[minNeighborPos(j, i).second][minNeighborPos(j, i).first] >= 2)
                {
                    dijkstraMap[i][j] = dijkstraMap[minNeighborPos(j, i).second][minNeighborPos(j, i).first] + 1;
                    changed = true;
                }
    }
}

void Pathfinding::calculateInversedDijkstraMap(int destination_x, int destination_y)
{
    if (dijkstraMap[destination_y][destination_x] != 0)
        calculateDijkstraMap(destination_x, destination_y, dijkstraMap);

    for (int i = 0; i < map_y; i++)
        for (int j = 0; j < map_x; j++)
            inversedDijkstraMap[i][j] = dijkstraMap[i][j] * (-1.2);

    calculateDijkstraMap(destination_x, destination_y, inversedDijkstraMap);
}

pair<int, int> Pathfinding::minNeighborPos(int x, int y)
{
    float min = dijkstraMap[y][x];
    pair<int, int> minPos(x, y);

    pair<int, int> neighborsPos[4] = {pair<int, int>(x, y - 1), pair<int, int>(x - 1, y),
                                      pair<int, int>(x, y + 1), pair<int, int>(x + 1, y)};

    for (int i = 0; i < 4; i++)
    {
        if (neighborsPos[i].second > map_y - 1 || neighborsPos[i].second < 0 ||
                neighborsPos[i].first > map_x - 1 || neighborsPos[i].first < 0 ||
                !map->tileIsPassable(neighborsPos[i].first, neighborsPos[i].second))
            continue;
        if (dijkstraMap[neighborsPos[i].second][neighborsPos[i].first] < min)
        {
            min = dijkstraMap[neighborsPos[i].second][neighborsPos[i].first];
            minPos = neighborsPos[i];
        }
    }

    return minPos;
}

pair<int, int> Pathfinding::maxNeighborPos(int x, int y)
{
    float max = inversedDijkstraMap[y][x];
    pair<int, int> maxPos(x, y);

    pair<int, int> neighborsPos[4] = {pair<int, int>(x, y - 1), pair<int, int>(x - 1, y),
                                      pair<int, int>(x, y + 1), pair<int, int>(x + 1, y)};

    for (int i = 0; i < 4; i++)
    {
        if (neighborsPos[i].second > map_y - 1 || neighborsPos[i].second < 0 ||
                neighborsPos[i].first > map_x - 1 || neighborsPos[i].first < 0 ||
                !map->tileIsPassable(neighborsPos[i].first, neighborsPos[i].second))
            continue;
        if (inversedDijkstraMap[neighborsPos[i].second][neighborsPos[i].first] > max)
        {
            max = inversedDijkstraMap[neighborsPos[i].second][neighborsPos[i].first];
            maxPos = neighborsPos[i];
        }
    }

    return maxPos;
}

