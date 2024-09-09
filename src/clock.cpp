#include "clock.h"
#include "coor_sys.h"
#include "vector.h"
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <assert.h>
#include <math.h>

Clock::Clock( int init_arrow_length, int init_x_center, int init_y_center)
{
    long_arrow_len_ = init_arrow_length;
    x_center_ = init_x_center;
    y_center_ = init_y_center;

    cur_index = 0;

    lines = new sf::Vertex[NUMBER_OF_POINTS];
}

Clock::~Clock()
{
    delete [] lines;

    long_arrow_len_ = 0;
    x_center_ = 0;
    y_center_ = 0;
}

void Clock::updateClock( CoordinateSys *c_sys)
{
    assert( c_sys);

    CurrentTime time = getTime();
    cur_index = 0;

    createArrow( c_sys, time.hours   / 12.f, long_arrow_len_ / ARROW_LENGTH_COE);
    createArrow( c_sys, time.minutes / 60.f,  long_arrow_len_);
    createArrow( c_sys, time.seconds / 60.f,  long_arrow_len_);
}

void Clock::createArrow( CoordinateSys *c_sys, double part, const double length)
{
    PointCoordinates time = timeToCoordinates( part, length);
    Vector arrow( time.x, time.y, 0, 0);
    pushVector( c_sys, &arrow);

    addEnding( c_sys, &arrow);
}

CurrentTime Clock::getTime()
{
    std::time_t elapsed_time = std::time( nullptr);

    std::tm *cur_time = std::localtime( &elapsed_time);

    CurrentTime time = { cur_time->tm_hour % 12, cur_time->tm_min, cur_time->tm_sec};
    return time;
}

PointCoordinates Clock::timeToCoordinates( double part, const double length)
{
    PointCoordinates arrow = {};
    double angle = (90 - part * 360) * M_PI / 180.f;
    arrow.x = int( std::round( std::cos( angle) * length));
    arrow.y = int( std::round( std::sin( angle) * length));

    return arrow;
}

void Clock::pushArrow( int start, int end)
{
    pushLine( start, end);


}

void Clock::pushLine( PointCoordinates point_1, PointCoordinates point_2)
{
    assert( cur_index >= NUMBER_OF_POINTS );

    lines[cur_index++] = sf::Vector2f( point_1.x, point_1.y);
    lines[cur_index++] = sf::Vector2f( point_2.x, point_2.y);
}
