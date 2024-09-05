#ifndef COORDINATE_SYSTEM_FUNCTIONS
#define COORDINATE_SYSTEM_FUNCTIONS

#include "vector.h"
#include <vector>

struct CoordinateSys
{
    int x_center;
    int y_center;
    std::vector< Vector> vectors;

    CoordinateSys( int w_width, int w_height);
};

#endif // COORDINATE_SYSTEM_FUNCTIONS
