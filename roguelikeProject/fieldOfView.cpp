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

            if (temp_x > map_x - 1 || temp_x < 0 || temp_y > map_y - 1 || temp_y < 0)
                break;
            map->setTileSeen(round(temp_x), round(temp_y), true);
            if (!map->getTerrainTileAt(round(temp_x), round(temp_y)).getPassability())
                break;
        }
    }
}

bool FieldOfView::lineOfSight(int x1, int y1, int x2, int y2, Map *map, int maxLength)
{
    float length = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    if (length > maxLength)
        return false;

    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if (steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if (x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = y1;

    const int maxX = x2;

    for (int x = x1; x < maxX; x++)
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
            y += ystep;
            error += dx;
        }
    }

    return true;
}
