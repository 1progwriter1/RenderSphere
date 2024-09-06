#include "vector.h"
#include "coor_sys.h"
#include <cassert>
#include <chrono>
#include <cmath>

const double EPSILON = 1e-6;
const double ENDING_SIZE_CF = 5.f;

Vector::Vector( int x, int y, int x_0, int y_0)
{
    this->x = x;
    this->x_0 = x_0;
    this->y = y;
    this->y_0 = y_0;

    is_length_real = false;
}

Coordinates Vector::getCoordinates()
{
    Coordinates tmp = {x, y, x_0, y_0};
    return tmp; // c++11 extension
}

Vector Vector::addVector( Vector vec)
{
    vec.x += x - vec.x_0;
    vec.y += y - vec.y_0;

    return Vector( x + vec.x, y + vec.y, x_0, y_0);
}

Vector Vector::divide( double cf)
{
    assert( std::fabs( cf) >= EPSILON);

    x = int( std::round( x / cf));
    y = int( std::round( y / cf));

    return *this;
}

double Vector::getLength()
{
    if ( !is_length_real )
    {
        is_length_real = true;
        length = sqrt( pow( x - x_0, 2) + pow( y - y_0, 2));
    }

    return length;
}

void Vector::setLength( double new_length)
{
    double cur_length = getLength();
    x = int( std::round( x / cur_length * new_length));
    y = int( std::round( y / cur_length * new_length));
} // shadow

void addEnding( CoordinateSys *c_sys, Vector *vec)
{
    assert( vec );
    assert( c_sys->lines.size() > 0 );

    Coordinates vec_c = vec->getCoordinates();
    double length = vec->getLength() / ENDING_SIZE_CF;

    Vector reversed( vec_c.x_0, vec_c.y_0, vec_c.x, vec_c.y_0);
    reversed.setLength( length);
    Vector perpendicular_1( -vec_c.y, vec_c.x, vec_c.x_0, vec_c.y_0);
    perpendicular_1.setLength( length);

    Vector part = perpendicular_1.addVector( reversed);
    pushVector( c_sys, &part);

    Vector perpendicular_2( vec_c.y, -vec_c.x, vec_c.x_0, vec_c.y_0);
    perpendicular_2.setLength( length);

    part = perpendicular_2.addVector( reversed);
    pushVector( c_sys, &part);
}
