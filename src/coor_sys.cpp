#include "coor_sys.h"

PointCoordinates CoordinateSys::translateToPixels( PointCoordinates point)
{
    int x = point.x + x_center;
    int y = y_center - point.y;

    return {x, y};
}
