#ifndef DRAW_VECTOR_FUNCTIONS
#define DRAW_VECTOR_FUNCTIONS

struct Coordinates
{
    int x;
    int y;
    int x_0;
    int y_0;
};

class Vector
{
    int x;
    int y;
    int x_0;
    int y_0;

    double length;
    bool is_length_real;

public:
    Vector( int x, int y, int x_0, int y_0);
    Coordinates getCoordinates();
    Vector addVector( Vector vec);
    Vector divide( double cf);
    double getLength();
    void setLength( double new_length);
};

#include "coor_sys.h"

void addEnding( CoordinateSys *c_sys, Vector *vec);

#endif // DRAW_VECTOR_FUNCTIONS
