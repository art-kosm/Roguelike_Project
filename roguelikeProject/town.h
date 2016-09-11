#pragma once

#include "map.h"

class Map;
class Town : public Map
{
public:
    Town(const string &name);

private:
    void addCitizens(int number);
    void addTraders(int number);
    void addHousesAndLakes(int housesNumber, int lakesNumber);
};
