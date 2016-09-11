#include "aggressiveAI.h"
#include "fieldOfView.h"

AggressiveAI::AggressiveAI()
{}

void AggressiveAI::takeTurn(Actor *actor, Actor *player)
{
    Map *map = actor->getMap();
    int actorX = actor->getX();
    int actorY = actor->getY();
    int playerX = player->getX();
    int playerY = player->getY();

    int horizontalDistance = playerX - actorX;
    int verticalDistance = playerY - actorY;

    if (FieldOfView::lineOfSight(actorX, actorY, playerX, playerY, map, actor->getPerceptionRadius()))
    {
        int newX = actorX;
        int newY = actorY;
        int diffX = (horizontalDistance > 0) ? 1 : ((horizontalDistance < 0) ? -1 : 0);
        int diffY = (verticalDistance > 0) ? 1 : ((verticalDistance < 0) ? -1 : 0);

        if (abs(horizontalDistance) > abs(verticalDistance))
            newX += diffX;
        else if (map->tileIsPassable(actorX, actorY + diffY) && !map->isWater(actorX, actorY + diffY))
            newY += diffY;
        else
            newX += diffX;

        if (playerX == newX && playerY == newY)
        {
            actor->attack(player);
            return;
        }

        actor->move(newX, newY);
    }
    else if (rand() % 2)
        actor->move(rand() % 2 ? actorX - 1 : actorX + 1, actorY);
    else
        actor->move(actorX, rand() % 2 ? actorY - 1 : actorY + 1);
}
