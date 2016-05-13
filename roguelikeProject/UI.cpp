#include "UI.h"

UI::UI()
{
	statusBar = createNewWindow(status_bar_y, status_bar_x, 0, 0);
	statsBar = createNewWindow(stats_bar_y, stats_bar_x, 0, term_y - stats_bar_y);
}

UI::~UI()
{
	destroyWindow(statusBar);
	destroyWindow(statsBar);
}

void UI::refresh()
{
	wrefresh(statusBar);
	wrefresh(statsBar);
}

void UI::writeToStatusBar(const std::string &message)
{
	wprintw(statusBar, message.c_str());
	wrefresh(statusBar);
}

void UI::writeToStatsBar(const std::string &message)
{
	wprintw(statsBar, message.c_str());
	wrefresh(statsBar);
}

void UI::clearStatusBar()
{
	werase(statusBar);
	//wrefresh(statusBar);
}

void UI::clearStatsBar()
{
	werase(statsBar);
}

void UI::browseInventory(Actor *actor)
{
	scr_dump("temp.scr");
	openInventoryWindow();
	Inventory *inventory = actor->getInventory();
	vector<Item *>items = inventory->getItems();
	printInventory(actor);

	bool finished = false;
	Item *currentItem = items.front();
	int currentItemPos = 0;
	while (!finished)
	{
		wattron(inventoryWindow, A_UNDERLINE);
		mvwprintw(inventoryWindow, currentItemPos + 1, 4, items.at(currentItemPos)->getName().c_str());
		wrefresh(inventoryWindow);
		wattroff(inventoryWindow, A_UNDERLINE);

		int command = getch();
		switch (command)
		{
			case KEY_UP:
				if (currentItemPos == 0)
					break;
				mvwprintw(inventoryWindow, currentItemPos + 1, 4, items.at(currentItemPos)->getName().c_str());
				currentItemPos--;
				currentItem = items.at(currentItemPos);
				break;

			case KEY_DOWN:
				if ((unsigned)currentItemPos == items.size() - 1)
					break;
				mvwprintw(inventoryWindow, currentItemPos + 1, 4, items.at(currentItemPos)->getName().c_str());
				currentItemPos++;
				currentItem = items.at(currentItemPos);
				break;

			case 'w':
				if (currentItem->getType() != "weapon")
				{
					clearStatusBar();
					writeToStatusBar("This is not a weapon!");
					break;
				}
				inventory->equipWeapon(dynamic_cast<Weapon *>(currentItem));
				clearStatusBar();
				writeToStatusBar("Equipped " + currentItem->getName() + "!");
				break;

			case 'a':
				if (currentItem->getType() != "armor")
				{
					clearStatusBar();
					writeToStatusBar("This is not an armor!");
					break;
				}
				inventory->equipArmor(dynamic_cast<Armor *>(currentItem));
				clearStatusBar();
				writeToStatusBar("Equipped " + currentItem->getName() + "!");
				break;

			case 'd':
				actor->dropItem(currentItem);
				items = inventory->getItems();
				werase(inventoryWindow);
				box(inventoryWindow, 0, 0);
				printInventory(actor);
				currentItemPos = 0;
				currentItem = items.front();
				break;

			case 'q':
				finished = true;
				break;
			default:
				break;
		}
		wrefresh(inventoryWindow);
	}
	destroyWindow(inventoryWindow);
	scr_restore("temp.scr");
	remove("temp.scr");
}

void UI::openInventoryWindow()
{
	inventoryWindow = createNewWindow(term_y / 3, term_x / 3, term_y / 2 - term_y / 3, term_x / 2 - term_x / 3);
	box(inventoryWindow, 0, 0);
}

WINDOW *UI::createNewWindow(int height, int width, int start_x, int start_y)
{
	WINDOW *window;

	window = newwin(height, width, start_y, start_x);
	wrefresh(window);

	return window;
}

void UI::destroyWindow(WINDOW *window)
{
	wrefresh(window);
	wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	delwin(window);
}

void UI::printInventory(Actor *actor)
{
	Inventory *inventory = actor->getInventory();
	vector<Item *>items = inventory->getItems();
	for (int i = 0; (unsigned)i < items.size(); i++)
	{
		mvwprintw(inventoryWindow, i + 1, 1, (std::to_string(i + 1) + ".").c_str());
		mvwprintw(inventoryWindow, i + 1, 4, items.at(i)->getName().c_str());
	}
	wrefresh(inventoryWindow);
}

