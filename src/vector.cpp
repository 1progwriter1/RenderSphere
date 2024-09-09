#include "vector.h"
#include <cassert>
#include <chrono>
#include <cmath>

const double EPSILON = 1e-6;
const double ENDING_SIZE_CF = 10.f;

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
    return {x, y, x_0, y_0};
}

Vector Vector::addVector( Vector vec)
{
    vec.x += x_0 - vec.x_0;
    vec.y += y_0 - vec.y_0;

    assert( x_0 == vec.x_0);
    assert( y_0 == vec.y_0);

    return Vector( x + vec.x - vec.x_0, y + vec.y - vec.y_0, x_0, y_0);
}

Vector Vector::divide( double cf)
{
    assert( std::fabs( cf) >= EPSILON);

    x = x_0 + int( std::round( (x - x_0) / cf));
    y = y_0 + int( std::round( (y - y_0) / cf));

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
}

void Vector::createEnding( Coordinates *end_1, Coordinates *end_2)
{
    assert( end_1);
    assert( end_2);

    Vector reversed = (~(*this)).divide( ENDING_SIZE_CF);

    Vector perpendicular = this->getPerpendicular().move( this->x, this->y).divide( ENDING_SIZE_CF);
    Vector part = perpendicular.addVector( reversed);
    *end_1 = part.getCoordinates();

    perpendicular = (~perpendicular).move( this->x, this->y);
    part = perpendicular.addVector( reversed);
    *end_2 = part.getCoordinates();
}

Vector Vector::operator ~()
{
    return Vector( x_0, y_0, x, y);
}

Vector Vector::move( int new_x_0, int new_y_0)
{
    x += new_x_0 - x_0;
    y += new_y_0 - y_0;
    x_0 = new_x_0;
    y_0 = new_y_0;

    return *this;
}

Vector Vector::getPerpendicular()
{
    int vec_x = x_0 + y_0 - y;
    int vec_y = -(y_0 + x_0 - x);
    return Vector (vec_x, vec_y, x_0, y_0);
}
