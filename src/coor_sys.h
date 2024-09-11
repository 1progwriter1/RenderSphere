#ifndef COORDINATE_SYSTEM_FUNCTIONS
#define COORDINATE_SYSTEM_FUNCTIONS

struct PointCoordinates
{
    int x;
    int y;
};

class CoordinateSys
{
    int x_center;
    int y_center;

public:
    CoordinateSys( int w_width, int w_height)
        : x_center( w_width / 2), y_center( w_height / 2) {};
    ~CoordinateSys() {};

    PointCoordinates translateToPixels( const PointCoordinates &point) const;
    PointCoordinates translateFromPixels( const PointCoordinates &point) const;
};

#endif // COORDINATE_SYSTEM_FUNCTIONS
