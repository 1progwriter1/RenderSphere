#include "coor_sys.h"
#include <cassert>
#include <cinttypes>
#include <cstddef>
#include <cstdio>
#include <sys/_types/_suseconds_t.h>
#include <sys/errno.h>
#include "../MyLibraries/headers/systemdata.h"
#include "vector.h"
#include "clock.h"

static int getX( CoordinateSys *c_sys, size_t index);
static int getY( CoordinateSys *c_sys, size_t index);
static int checkMemory( WindowData *data, size_t num_of_vec);

CoordinateSys::CoordinateSys( int w_width, int w_height)
{
    x_center = w_width / 2;
    y_center = w_height / 2;
}

void updateLines( WindowData *data, CoordinateSys *c_sys)
{
    assert( data);
    assert( c_sys);

    updateClock( c_sys);

    size_t num_of_vec = c_sys->lines.size();
    if ( checkMemory( data, num_of_vec) != SUCCESS )
    {
        return;
    }
    for ( size_t i = 0; i < num_of_vec; i++ )
    {
        data->lines[i] = sf::Vertex( sf::Vector2f( getX( c_sys, i), getY( c_sys, i)));
    }
}

static int getX( CoordinateSys *c_sys, size_t index)
{
    assert( c_sys);

    PointCoordinates vec = c_sys->lines.data()[index];

    return vec.x;
}

static int getY( CoordinateSys *c_sys, size_t index)
{
    assert( c_sys);

    PointCoordinates vec = c_sys->lines.data()[index];

    return vec.y;
}

static int checkMemory( WindowData *data, size_t num_of_vec)
{
    assert( data);

    if ( data->num_of_lines != num_of_vec )
    {
        if ( data->num_of_lines != 0 )
            delete [] data->lines;
        data->lines = new sf::Vertex[num_of_vec];
        data->num_of_lines = num_of_vec;
        if ( !data->lines )
        {
            printf( RED "error: " END_OF_COLOR "failed to update lines\n");
            return ERROR;
        }
    }

    return SUCCESS;
}

void pushVector( CoordinateSys *c_sys, Vector *vec)
{
    assert( c_sys);
    assert( vec);

    Coordinates vec_c = vec->getCoordinates();
    PointCoordinates point = {};

    point.x = c_sys->x_center + vec_c.x_0;
    point.y = c_sys->y_center - vec_c.y_0;
    c_sys->lines.push_back( point);

    point.x = c_sys->x_center + vec_c.x;
    point.y = c_sys->y_center - vec_c.y;
    c_sys->lines.push_back( point);
}

void clearLines( CoordinateSys *c_sys)
{
    assert( c_sys);

    while ( !c_sys->lines.empty() )
    {
        c_sys->lines.pop_back();
    }
}
