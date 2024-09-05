#include "vector.h"

Vector::Vector( int x, int y, int x_0, int y_0)
{
    this->x = x;
    this->x_0 = x_0;
    this->y = y;
    this->y_0 = y_0;
}

Coordinates Vector::getCoordinates()
{
    Coordinates tmp = {x, y, x_0, y_0};
    return tmp; // c++11 extension
}

Vector addVectors( Vector vec1, Vector vec2)
{
    return Vector( vec1.x + vec2.x, vec1.y + vec2.y, vec1.x_0, vec2.y_0);
}
