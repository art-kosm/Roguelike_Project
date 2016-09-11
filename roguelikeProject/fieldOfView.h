#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "map.h"

class FieldOfView
{
public:
    FieldOfView();
    /// Uses raycasting.
    /// Sets tiles seen or not during the process.
    /// Does NOT use the following LOS function.
    static void calculate(int x, int y, Map *map, int radius);
    /// Bresenham's line algorithm implementation
    static bool lineOfSight(int x1, int y1, int x2, int y2, Map *map, int maxLength);
};

