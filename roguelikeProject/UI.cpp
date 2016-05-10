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
}

void UI::writeToStatsBar(const std::string &message)
{
	wprintw(statsBar, message.c_str());
}

void UI::clearStatusBar()
{
	werase(statusBar);
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
	delwin(window);
}

