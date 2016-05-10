#include "gameController.h"

GameController::GameController()
{
	ui = new UI();
	ui->writeToStatusBar("TTEST");

	worldMap = new Map();
	worldMap->setName("World map");
	worldMap->addDungeon(new Dungeon("Right dungeon", 4, '*', 0, map_x / 2 + 2, map_y / 2));
	worldMap->addDungeon(new Dungeon("Left dungeon", 4, '*', 0, map_x / 2 - 2, map_y / 2));

	worldMap->getDungeonByName("Right dungeon")->setLevel(1, new Map("testMap_30x10.txt"));
	Map *rightDungeonSecondLevel = worldMap->getDungeonByName("Right dungeon")->getLevel(1);
	rightDungeonSecondLevel->addActor(new Actor("AI-driven orc!", "humanoid", 'o', map_x / 2, map_y / 2, 10, 5, new CowardlyAI(), rightDungeonSecondLevel));

	player = new Actor("player", "player", '@', map_x / 2, map_y / 2, 1, 7, new PlayerAI(), worldMap);
	player->setSeen(true);
	currentDungeon = nullptr;
	currentMap = worldMap;
	state = playing;

	ui->writeToStatsBar("HP:" + std::to_string(player->getHP()));
}

GameController::~GameController()
{
	delete ui;
	delete worldMap;
	delete player;
}

void GameController::draw()
{
	FieldOfView::calculate(player->getX(), player->getY(), currentMap, player->getPerceptionRadius());
	currentMap->draw(status_bar_y);
	player->draw(status_bar_y);
	ui->refresh();
}

void GameController::processTurn()
{
	ui->clearStatusBar();

	char command = getch();
	Entrance *entrance = nullptr;
	Entrance *pairingEntrance = nullptr;
	Map *previousMap = nullptr;
	switch (command)
	{
	case '4':
		player->move(player->getX() - 1, player->getY());
		break;
	case '6':
		player->move(player->getX() + 1, player->getY());
		break;
	case '8':
		player->move(player->getX(), player->getY() - 1);
		break;
	case '2':
		player->move(player->getX(), player->getY() + 1);
		break;
	case '7':
		player->move(player->getX() - 1, player->getY() - 1);
		break;
	case '9':
		player->move(player->getX() + 1, player->getY() - 1);
		break;
	case '1':
		player->move(player->getX() - 1, player->getY() + 1);
		break;
	case '3':
		player->move(player->getX() + 1, player->getY() + 1);
		break;
	case 'e':
		entrance = currentMap->getEntranceOn(player->getX(), player->getY());
		if (entrance == nullptr)
		{
			ui->writeToStatusBar("Unable to enter!");
			break;
		}

		previousMap = currentMap;
		currentMap = entrance->getLeadsTo();
		pairingEntrance = currentMap->getEntranceByLeadsTo(previousMap);
		player->move(pairingEntrance->getX(), pairingEntrance->getY());
		player->setMap(currentMap);
		ui->writeToStatusBar("You entered " + currentMap->getName() + "!");
		break;
	case 'q':
		state = over;
		break;
	}

	currentMap->processActorsTurns(player);
}

bool GameController::gameIsOver()
{
	return state == over;
}
