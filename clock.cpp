#include "clock.h"
#include "coor_sys.h"
#include "vector.h"
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <assert.h>
#include <math.h>

const double ARROW_LENGTH = 100;

struct CurrentTime
{
    size_t hours;
    size_t minutes;
    size_t seconds;
};

struct ArrowCoordinates
{
    int x;
    int y;
};

static CurrentTime getTime();
static ArrowCoordinates timeToCoordinates( double part);

void createArrows( sf::Vertex lines[], CoordinateSys &sys)
{
    CurrentTime time = getTime();

    lines[0] = sf::Vertex( sf::Vector2f( sys.x_center, sys.y_center), sf::Color::Green);
    ArrowCoordinates hours = timeToCoordinates( time.hours / 12.f);
    lines[1] = sf::Vertex( sf::Vector2f( sys.x_center + hours.x, sys.y_center - hours.y), sf::Color::Green);
    lines[2] = sf::Vertex( sf::Vector2f( sys.x_center, sys.y_center), sf::Color::Yellow);
    ArrowCoordinates minutes = timeToCoordinates( time.minutes / 60.f);
    lines[3] = sf::Vertex( sf::Vector2f( sys.x_center + minutes.x, sys.y_center - minutes.y), sf::Color::Yellow);
    lines[4] = sf::Vertex( sf::Vector2f( sys.x_center, sys.y_center), sf::Color::White);
    ArrowCoordinates seconds = timeToCoordinates( time.seconds / 60.f);
    lines[5] = sf::Vertex( sf::Vector2f( sys.x_center + seconds.x, sys.y_center - seconds.y), sf::Color::White);
}

static CurrentTime getTime()
{
    std::time_t elapsed_time = std::time( nullptr);

    std::tm *cur_time = std::localtime( &elapsed_time);

    CurrentTime time = { cur_time->tm_hour % 12, cur_time->tm_min, cur_time->tm_sec};
    return time;
}

static ArrowCoordinates timeToCoordinates( double part)
{

    ArrowCoordinates arrow = {};
    double angle = (90 - part * 360) * M_PI / 180.f;
    arrow.x = int( std::round( std::cos( angle) * ARROW_LENGTH));
    arrow.y = int( std::round( std::sin( angle) * ARROW_LENGTH));

    return arrow;
}


