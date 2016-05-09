#include "aggressiveAI.h"

AggressiveAI::AggressiveAI()
{

}

void AggressiveAI::takeTurn(Actor *actor, Actor *player)
{
	Map *map = actor->getMap();
	if (FieldOfView::lineOfSight(actor->getX(), actor->getY(), player->getX(), player->getY(), map,
								 actor->getPerceptionRadius()))
	{
		pair<int, int> step = map->getPathfinding()->nextStepTowards(actor->getX(), actor->getY(),
																	 player->getX(), player->getY());
		actor->move(step.first, step.second);
	}
}


