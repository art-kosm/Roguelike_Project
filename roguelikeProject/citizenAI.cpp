#include "citizenAI.h"
#include "actor.h"
#include "fieldOfView.h"

CitizenAI::CitizenAI()
{}

void CitizenAI::takeTurn(Actor *actor, Actor *)
{
    int actorX = actor->getX();
    int actorY = actor->getY();
    int turn = rand() % 6;

    if (turn % 5 == 0)
    {
        if (turn == 0)
            actor->move(rand() % 2 ? actorX - 1 : actorX + 1, actorY);
        else
            actor->move(actorX, rand() % 2 ? actorY - 1 : actorY + 1);
    }
}

string CitizenAI::talk()
{
    if (rand() % 2)
        return "'Hello.'\n";
    return "'What a nice day'!\n";
}
