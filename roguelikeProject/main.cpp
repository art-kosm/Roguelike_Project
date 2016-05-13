#include <iostream>
#include <curses.h>

#include "gameController.h"
#include "generalConstants.h"

using namespace generalConstants;

int main()
{
	initscr();
	resize_term(term_y, term_x);
	raw();
	noecho();
	keypad(stdscr, true);
	curs_set(0);
	start_color();

	GameController *controller = new GameController();
	controller->draw();

	while (!controller->gameIsOver())
	{
		controller->processTurn();
		controller->draw();
	}

	controller->displayDeathMessage();
	getch();

	delete controller;

	endwin();
	return 0;
}

