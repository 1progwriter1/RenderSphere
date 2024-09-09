#ifndef VECTOR_CLOCK
#define VECTOR_CLOCK

#include "coor_sys.h"
#include <SFML/Graphics.hpp>
#include <cstddef>

struct CurrentTime
{
    int hours;
    int minutes;
    int seconds;
};

class Clock
{
public:
    sf::Vertex *lines;
    const size_t NUMBER_OF_POINTS = 18;

private:
    size_t cur_index;
    int x_center_;
    int y_center_;
    int long_arrow_len_;

    const double ARROW_LENGTH_COE = 5.f / 3.f;

public:
    Clock( int init_arrow_length, int init_x_center = 0, int init_y_center = 0);
    ~Clock();
    void updateClock( CoordinateSys *c_sys);

private:
    CurrentTime getTime();
    PointCoordinates timeToCoordinates( double part, const double length);
    void createArrow( CoordinateSys *c_sys, double part, const double length);
    void pushArrow( CoordinateSys *c_sys, PointCoordinates start, PointCoordinates end);
    void pushLine( PointCoordinates point_1, PointCoordinates point_2);
};


#endif // VECTOR_CLOCK
