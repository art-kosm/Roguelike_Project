#include "cowardlyAI.h"
#include "fieldOfView.h"

CowardlyAI::CowardlyAI()
{}

int CowardlyAI::distance(int actorX, int actorY, int playerX, int playerY)
{
    return abs(playerX - actorX) + abs(playerY - actorY);
}

void CowardlyAI::takeTurn(Actor *actor, Actor *player)
{
    Map *map = actor->getMap();
    int actorX = actor->getX();
    int actorY = actor->getY();
    int playerX = player->getX();
    int playerY = player->getY();
    int dist = distance(actorX, actorY, playerX, playerY);

    if (FieldOfView::lineOfSight(actorX, actorY, playerX, playerY, map, actor->getPerceptionRadius()))
    {
        if (actorX < map_x - 1)
            if (map->tileIsPassable(actorX + 1, actorY) && distance(actorX + 1, actorY, playerX, playerY) > dist)
            {
                actor->move(actorX + 1, actorY);
                return;
            }
        if (actorX > 0)
            if (map->tileIsPassable(actorX - 1, actorY) && distance(actorX - 1, actorY, playerX, playerY) > dist)
            {
                actor->move(actorX - 1, actorY);
                return;
            }
        if (actorY < map_y - 1)
            if (map->tileIsPassable(actorX, actorY + 1) && distance(actorX, actorY + 1, playerX, playerY) > dist)
            {
                actor->move(actorX, actorY + 1);
                return;
            }
        if (actorY > 0)
            if (map->tileIsPassable(actorX, actorY - 1) && distance(actorX, actorY - 1, playerX, playerY) > dist)
            {
                actor->move(actorX, actorY - 1);
                return;
            }
    }
    else if (rand() % 2)
        actor->move(rand() % 2 ? actorX - 1 : actorX + 1, actorY);
    else
        actor->move(actorX, rand() % 2 ? actorY - 1 : actorY + 1);
}
