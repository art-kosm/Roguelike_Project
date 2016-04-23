#include <iostream>
#include <curses.h>

#include "dungeon.h"
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


	Dungeon *dungeon = new Dungeon(4, 0);
	Map *level = dungeon->getCurrentLevel();
	level->setTile(TerrainElement("Impassable", "wall", '#', false), 40, 40);
	int ch = 0;
	bool exit = false;
	while(!exit)
	{
		erase();
		level->draw();
		ch = getch();
		switch (ch)
		{
		case '4':
			level->movePlayer(level->getPlayer()->getX() - 1, level->getPlayer()->getY());
			break;
		case '6':
			level->movePlayer(level->getPlayer()->getX() + 1, level->getPlayer()->getY());
			break;
		case '8':
			level->movePlayer(level->getPlayer()->getX(), level->getPlayer()->getY() - 1);
			break;
		case '2':
			level->movePlayer(level->getPlayer()->getX(), level->getPlayer()->getY() + 1);
			break;
		case '7':
			level->movePlayer(level->getPlayer()->getX() - 1, level->getPlayer()->getY() - 1);
			break;
		case '9':
			level->movePlayer(level->getPlayer()->getX() + 1, level->getPlayer()->getY() - 1);
			break;
		case '1':
			level->movePlayer(level->getPlayer()->getX() - 1, level->getPlayer()->getY() + 1);
			break;
		case '3':
			level->movePlayer(level->getPlayer()->getX() + 1, level->getPlayer()->getY() + 1);
			break;
		case '>':
			dungeon->moveDown();
			level = dungeon->getCurrentLevel();
			break;
		case '<':
			dungeon->moveUp();
			level = dungeon->getCurrentLevel();
			break;
		case KEY_F(1):
			exit = true;
			break;
		}
	}
	delete dungeon;

	endwin();
	return 0;
}

