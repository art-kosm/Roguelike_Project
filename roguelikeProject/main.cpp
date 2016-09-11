#include <iostream>
#include <ctime>
#include <curses.h>

#include "gameController.h"
#include "generalConstants.h"

using namespace generalConstants;

int main()
{    
    srand(time(0));

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

    controller->displayScore();
    getch();

    delete controller;

    endwin();
    return 0;
}

