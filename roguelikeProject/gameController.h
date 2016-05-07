#pragma once

#include "dungeon.h"
#include "actor.h"
#include "map.h"
#include "fieldOfView.h"

enum GameState
{
	playing,
	over
};

class GameController
{
public:
	GameController();
	~GameController();
	void draw();
	void processTurn();
	bool gameIsOver();

private:
	Map *worldMap;
	Actor *player;
	Dungeon *currentDungeon;
	Map *currentMap;
	GameState state;
};
