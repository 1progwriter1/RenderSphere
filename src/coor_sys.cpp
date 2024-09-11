#include "coor_sys.h"

PointCoordinates CoordinateSys::translateToPixels( const PointCoordinates &point) const
{
    int x = point.x + x_center;
    int y = y_center - point.y;

    return {x, y};
}

PointCoordinates CoordinateSys::translateFromPixels( const PointCoordinates &point) const
{
    int x = point.x - x_center;
    int y = -(point.y - y_center);

    return {x, y};
}
