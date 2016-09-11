#pragma once

#include <iostream>
//#include "tile.h"
#include "generalConstants.h"
#include "map.h"
#include "AI.h"
#include "inventory.h"

enum Status
{
    ALIVE,
    DEAD,
    DROWNED
};

using std::string;
using namespace generalConstants;

class AI;
class Map;
class Actor : public Tile
{
public:
    Actor();
    Actor(const string &name, Type type, char symbol, int x, int y, int hp,
          int perceptionRadius, AI *mind, Map *locatedOn = nullptr);

    void setMap(Map *map);
    void setAI(AI *mind);

    int getHP();
    int getMP();
    int getMoney();
    int getLevel();
    int getExp();
    int getX();
    int getY();
    int getPerceptionRadius();
    Map *getMap();
    int getMaxHP();

    void draw(int indent = 0);
    void takeTurn(Actor *player);
    void move(int x, int y);
    void takeDamage(int damage);
    void restoreHP(int healed);
    bool isAlive();
    Inventory *getInventory();
    Item *pickUpItem();
    void dropItem(Item *item);
    void attack(Actor *actor);
    int askPrice(Item *item);
    void takeMoney(int money);
    void giveMoney(int money);
    void addExp(int exp);
    string talk();
    bool drowned();
    string castAFlood();

protected:
    int hp;
    int mp;
    int maxHP;
    int money;
    int level;
    int exp;

    int x;
    int y;
    int perceptionRadius;
    AI *mind;
    Map *locatedOn;
    Status status;
    Inventory *inventory;
};

