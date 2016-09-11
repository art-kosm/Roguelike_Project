#pragma once

#include "map.h"
#include "generalConstants.h"

using namespace generalConstants;

using std::pair;

class Map;
class Pathfinding
{
public:
    Pathfinding(Map *map);
    ~Pathfinding();
    pair<int, int> nextStepTowards(int start_x, int start_y, int destination_x, int destination_y);
    pair<int, int> nextStepAway(int start_x, int start_y, int destination_x, int destination_y);
    int getDistance(int x1, int y1, int x2, int y2);

private:
    void calculateDijkstraMap(int destination_x, int destination_y, float **dijkstraMap);
    void calculateInversedDijkstraMap(int destination_x, int destination_y);
    pair<int, int> minNeighborPos(int x, int y);
    pair<int, int> maxNeighborPos(int x, int y);

    float **dijkstraMap;
    float **inversedDijkstraMap;
    Map *map;
};
