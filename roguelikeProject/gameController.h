#pragma once

#include "UI.h"
#include "dungeon.h"
#include "actor.h"
#include "map.h"
#include "fieldOfView.h"
#include "aggressiveAI.h"
#include "cowardlyAI.h"
#include "playerAI.h"

enum GameState
{
	playing,
	over
};

class Actor;
class Dungeon;
class GameController
{
public:
	GameController();
	~GameController();
	void draw();
	void processTurn();
	bool gameIsOver();
	void displayDeathMessage();

private:
	Map *worldMap;
	Actor *player;
	Dungeon *currentDungeon;
	Map *currentMap;
	GameState state;
	UI *ui;
};
