#pragma once

//#define SMALL
//#define MEDIUM

namespace generalConstants
{
/*#ifdef SMALL
	const int map_x = 30;
	const int map_y = 10;*/
#ifdef MEDIUM
	const int map_x = 90;
	const int map_y = 30;
#else
	const int map_x = 150;
	const int map_y = 50;
#endif
	const int status_bar_x = map_x;
	const int status_bar_y = 3;
	const int stats_bar_x = map_x;
	const int stats_bar_y = 2;
	const int term_x = map_x;
	const int term_y = status_bar_y + stats_bar_y + 1 + map_y;
}
