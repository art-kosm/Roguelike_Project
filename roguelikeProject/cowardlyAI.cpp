#include "cowardlyAI.h"

CowardlyAI::CowardlyAI()
{

}

void CowardlyAI::takeTurn(Actor *actor, Actor *player)
{
	Map *map = actor->getMap();
	pair<int, int> step = map->getPathfinding()->nextStepAway(actor->getX(), actor->getY(),
																 player->getX(), player->getY());
	actor->move(step.first, step.second);
}

