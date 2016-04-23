#include <iostream>
#include <curses.h>

#include "map.h"
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

	Map *map = new Map();
	map->setTile(TerrainElement("Impassable", '#', false), 40, 40);
	int ch = 0;
	bool exit = false;
	while(!exit)
	{
		erase();
		map->draw();
		ch = getch();
		switch (ch)
		{
		case '4':
			map->movePlayer(map->getPlayer()->getX() - 1, map->getPlayer()->getY());
			break;
		case '6':
			map->movePlayer(map->getPlayer()->getX() + 1, map->getPlayer()->getY());
			break;
		case '8':
			map->movePlayer(map->getPlayer()->getX(), map->getPlayer()->getY() - 1);
			break;
		case '2':
			map->movePlayer(map->getPlayer()->getX(), map->getPlayer()->getY() + 1);
			break;
		case '7':
			map->movePlayer(map->getPlayer()->getX() - 1, map->getPlayer()->getY() - 1);
			break;
		case '9':
			map->movePlayer(map->getPlayer()->getX() + 1, map->getPlayer()->getY() - 1);
			break;
		case '1':
			map->movePlayer(map->getPlayer()->getX() - 1, map->getPlayer()->getY() + 1);
			break;
		case '3':
			map->movePlayer(map->getPlayer()->getX() + 1, map->getPlayer()->getY() + 1);
			break;
		case KEY_F(1):
			exit = true;
			break;
		}
	}
	delete map;

	endwin();
	return 0;
}

