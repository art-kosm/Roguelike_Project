#pragma once

#include <iostream>
#include <curses.h>

#include "generalConstants.h"
#include "inventory.h"
#include "actor.h"

using namespace generalConstants;
using std::string;

class UI
{
public:
	UI();
	~UI();
	void refresh();
	void writeToStatusBar(const string &message);
	void writeToStatsBar(const string &message);
	void clearStatusBar();
	void clearStatsBar();
	void browseInventory(Actor *actor);

private:
	WINDOW *statusBar;
	WINDOW *statsBar;
	WINDOW *inventoryWindow;

	void openInventoryWindow();
	WINDOW *createNewWindow(int height, int width, int start_x, int start_y);
	void destroyWindow(WINDOW *window);

	void printInventory(Actor *actor);
};

