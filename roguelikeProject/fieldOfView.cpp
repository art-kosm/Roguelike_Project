#include "fieldOfView.h"

FieldOfView::FieldOfView()
{

}

void FieldOfView::calculate(int x, int y, Map *map, int radius)
{
	map->setEverythingSeen(false);

	int rays = 360;
	int step = 3;

	for (int i = 0; i < rays + 1; i += step)
	{
		float dx = sin(i / (180 / M_PI));
		float dy = cos(i / (180 / M_PI));

		float temp_x = x;
		float temp_y = y;

		for (int j = 0; j < radius; j++)
		{
			temp_x += dx;
			temp_y += dy;

			if (temp_x > term_x - 1 || temp_x < 0 || temp_y > term_y - 1 || temp_y < 0)
				break;
			map->setTileSeen(round(temp_x), round(temp_y), true);
			if (!map->getTerrainTileAt(round(temp_x), round(temp_y)).getPassability())
				break;
		}
	}
}

bool FieldOfView::lineOfSight(int x1, int y1, int x2, int y2, Map *map)
{
	bool steep = abs(y2 - y1) > abs(x2 - x1);
	if (steep)
	{
		swap(x1, y1);
		swap(x2, y2);
	}
	if (x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int error = dx / 2;
	int yStep = 0;
	if (y1 < y2)
		yStep = 1;
	else
		yStep = -1;
	int y = y1;

	for (int x = x1; x <= x2; x++)
	{
		if (steep)
		{
			if (!map->getTerrainTileAt(y, x).getPassability())
				return false;
		}
		else
		{
			if (!map->getTerrainTileAt(x, y).getPassability())
				return false;
		}

		error -= dy;
		if (error < 0)
		{
			y += yStep;
			error += dx;
		}
	}
	return true;
}

void FieldOfView::swap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}

