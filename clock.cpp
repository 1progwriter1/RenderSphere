#include "clock.h"
#include "coor_sys.h"
#include "vector.h"
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <assert.h>
#include <math.h>

const double HOUR_ARROW_LENGTH = 60;
const double MIN_ARROW_LENGTH = 100;
const double SEC_ARROW_LENGTH = 100;

struct CurrentTime
{
    int hours;
    int minutes;
    int seconds;
};

static CurrentTime getTime();
static PointCoordinates timeToCoordinates( double part, const double length);
static void createArrow( CoordinateSys *c_sys, double part, const double length) ;

void updateClock( CoordinateSys *c_sys)
{
    assert( c_sys);

    CurrentTime time = getTime();

    clearLines( c_sys);

    createArrow( c_sys, time.hours / 12.f, HOUR_ARROW_LENGTH);
    createArrow( c_sys, time.minutes / 60.f, MIN_ARROW_LENGTH);
    createArrow( c_sys, time.seconds / 60.f, SEC_ARROW_LENGTH);
}

static void createArrow( CoordinateSys *c_sys, double part, const double length)
{
    PointCoordinates time = timeToCoordinates( part, length);
    Vector arrow( time.x, time.y, 0, 0);
    pushVector( c_sys, &arrow);

    // addEnding( c_sys, &arrow);
}

static CurrentTime getTime()
{
    std::time_t elapsed_time = std::time( nullptr);

    std::tm *cur_time = std::localtime( &elapsed_time);

    CurrentTime time = { cur_time->tm_hour % 12, cur_time->tm_min, cur_time->tm_sec};
    return time;
}

static PointCoordinates timeToCoordinates( double part, const double length)
{
    PointCoordinates arrow = {};
    double angle = (90 - part * 360) * M_PI / 180.f;
    arrow.x = int( std::round( std::cos( angle) * length));
    arrow.y = int( std::round( std::sin( angle) * length));

    return arrow;
}
