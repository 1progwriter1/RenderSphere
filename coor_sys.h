#ifndef COORDINATE_SYSTEM_FUNCTIONS
#define COORDINATE_SYSTEM_FUNCTIONS

#include "graphlib.h"
#include <vector>

struct PointCoordinates
{
    int x;
    int y;
};

struct CoordinateSys
{
    int x_center;
    int y_center;
    std::vector< PointCoordinates> lines;

    CoordinateSys( int w_width, int w_height);
};

#include "vector.h"

void updateLines( GraphWindow *data, CoordinateSys *c_sys);
void pushVector( CoordinateSys *c_sys, Vector *vec);
void clearLines( CoordinateSys *c_sys);

#endif // COORDINATE_SYSTEM_FUNCTIONS
