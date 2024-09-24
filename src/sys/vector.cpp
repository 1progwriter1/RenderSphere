#include "vector.hpp"
#include <cassert>
#include <cmath>

const double EPSILON = 1e-6;
const double ENDING_SIZE_CF = 10.f;

Vector::Vector( double init_x, double init_y, double init_x_0, double init_y_0, double init_z, double init_z_0)
{
    this->x = init_x;
    this->x_0 = init_x_0;
    this->y = init_y;
    this->y_0 = init_y_0;
    this->z = init_z;
    this->z_0 = init_z_0;

    is_length_real = false;
}

VectorCoordinates Vector::getCoordinates() const
{
    return {x, y, z, x_0, y_0, z_0};
}


Vector Vector::operator= ( const Vector &vec) const
{
    return Vector( vec.x, vec.y, vec.x_0, vec.y_0, vec.z, vec.z_0);
}

double Vector::getLength()
{
    if ( !is_length_real )
    {
        is_length_real = true;
        length = sqrt( pow( x - x_0, 2) + pow( y - y_0, 2) + pow( z - z_0, 2));
    }

    return length;
}

void Vector::setLength( double new_length)
{
    double cur_length = getLength();

    x = (x - x_0) / cur_length * new_length + x_0;
    y = (y - y_0) / cur_length * new_length + y_0;
    z = (z - z_0) / cur_length * new_length + z_0;

    is_length_real = false;
}

void Vector::createEnding( VectorCoordinates *end_1, VectorCoordinates *end_2) const
{
    assert( end_1);
    assert( end_2);

    Vector reversed = ~*this;
    reversed /= ENDING_SIZE_CF;

    Vector perpendicular = !*this;
    perpendicular.move( this->x, this->y, this->z);
    perpendicular /= ENDING_SIZE_CF;

    Vector part = perpendicular + reversed;
    *end_1 = part.getCoordinates();

    Vector perpendicular2 = ~perpendicular;
    perpendicular2.move( this->x, this->y, this->z);
    Vector part2 = perpendicular2 + reversed;
    *end_2 = part2.getCoordinates();
}

Vector &Vector::move( double new_x_0, double new_y_0, double new_z_0)
{
    x += new_x_0 - x_0;
    y += new_y_0 - y_0;
    z += new_z_0 - z_0;
    x_0 = new_x_0;
    y_0 = new_y_0;
    z_0 = new_z_0;

    return *this;
}

Vector operator+ ( const Vector &vec_1, const Vector &vec_2)
{
    VectorCoordinates fst = vec_1.getCoordinates();
    VectorCoordinates snd = vec_2.getCoordinates();

    Vector tmp = vec_2;
    tmp.move( fst.x, fst.y, fst.z);

    return Vector( fst.x + snd.x - snd.x_0, fst.y + snd.y - snd.y_0, fst.x_0, fst.y_0, fst.z + snd.z - snd.z_0, fst.z_0);
}

Vector operator- ( const Vector &vec_1, const Vector &vec_2)
{
    Vector tmp = vec_2;
    ~tmp;

    return vec_1 + tmp;
}

double operator* ( const Vector &vec_1, const Vector &vec_2)
{
    VectorCoordinates tmp_1 = vec_1.getCoordinates();
    VectorCoordinates tmp_2 = vec_2.getCoordinates();

    return (tmp_1.x - tmp_1.x_0) * (tmp_2.x - tmp_2.x_0) +
                    (tmp_1.y - tmp_1.y_0) * (tmp_2.y - tmp_2.y_0) +
                    (tmp_1.z - tmp_1.z_0) * (tmp_2.z - tmp_2.z_0);
}

Vector Vector::reflectNormal( Vector &normal)
{
    Vector normal_n = normalize( normal);
    double len = this->getLength();
    double angle = getAngle( *this, normal);

    normal_n.setLength( len);
    return  normal_n * 2 * angle - *this;
}

double getAngle( Vector &vec_1, Vector &vec_2)
{
    double len = vec_1.getLength() * vec_2.getLength();

    if ( fabs( len) < EPSILON)
    {
        return 0;
    }
    return vec_1 * vec_2 / len;
}


Vector normalize( Vector &vec)
{
    double len = vec.getLength();
    if ( fabs( len) < EPSILON ) return vec;
    VectorCoordinates coord = vec.getCoordinates();

    return Vector( coord.x_0 + (coord.x - coord.x_0) / len,
                    coord.y_0 + (coord.y - coord.y_0) / len,
                    coord.x_0,
                    coord.y_0,
                    coord.z_0 + (coord.z - coord.z_0) / len,
                    coord.z_0);
}


Vector operator* ( const Vector &vec, double cf)
{
    VectorCoordinates coord = vec.getCoordinates();

    return Vector( coord.x_0 + (coord.x - coord.x_0) * cf,
                    coord.y_0 + (coord.y - coord.y_0) * cf,
                    coord.x_0,
                    coord.y_0,
                    coord.z_0 + (coord.z - coord.z_0) * cf,
                    coord.z_0);
}


Vector operator/ ( const Vector &vec, double cf)
{
    assert( std::fabs( cf) >= EPSILON);

    Vector tmp = vec;

    tmp /= cf;

    return tmp;
}


// perpendicular
Vector operator! ( const Vector &vec)
{
    Vector tmp = vec;

    tmp != tmp;

    return tmp;
}


// reverse
Vector operator~ ( const Vector &vec)
{
    VectorCoordinates coord = vec.getCoordinates();

    return Vector( coord.x_0, coord.y_0, coord.x, coord.y, coord.z_0, coord.z);
}


Vector &Vector::operator/= ( double cf)
{
    assert( std::fabs( cf) >= EPSILON);

    x = x_0 + (x - x_0) / cf;
    y = y_0 + (y - y_0) / cf;
    z = z_0 + (z - z_0) / cf;

    return *this;
}


Vector &Vector::operator!= ( Vector &vec)
{
    assert( fabs( z) < EPSILON );
    assert( fabs( z_0) < EPSILON );

    double tmp_x_0 = this->x_0;
    double tmp_y_0 = this->y_0;
    this->move( 0, 0);
    double tmp_x = -this->y;
    this->y = this->x;
    this->x = tmp_x;
    this->move( tmp_x_0, tmp_y_0);

    return *this;
}
