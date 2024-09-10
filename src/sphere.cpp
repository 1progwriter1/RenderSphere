#include "sphere.h"
#include "vector.h"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdio>

const sf::Color BACKGROUND_COLOR = sf::Color( 255, 255, 255, 255);

Sphere::Sphere( unsigned int init_radius, unsigned int init_width, unsigned int init_height)
    : pixels_( sf::Points, init_width * init_height)
{
    radius_ = init_radius;
    width_  = init_width;
    height_ = init_height;

    light_ = { 234, (int) radius_ * 1, (int) radius_ * 5};

    length_ = width_ * height_;
}

Sphere::~Sphere()
{
    radius_ = 0;
    width_  = 0;
    height_ = 0;
    length_ = 0;
}

void Sphere::setPixels()
{
    for ( size_t y = 0; y < height_; y++ )
    {
        for ( size_t x = 0; x < width_; x++ )
        {
            size_t index = y * width_ + x;
            pixels_[index].position = sf::Vector2f( float( x), float( y));

            sf::Color color;
            if ( isInside( int( x), int(y )) )
            {
                color = getColor( int( x), int( y));
            } else
            {
                color = BACKGROUND_COLOR;
            }
            pixels_[index].color = color;
        }
    }
}

sf::Color Sphere::getColor( int x, int y)
{
    x =   x - (int) width_  / 2;
    y = -(y - (int) height_ / 2);
    int l_x = light_.x;
    int l_y = light_.y;
    int l_z = light_.z;
    int z_c = int( std::round( sqrt( pow( radius_, 2) - pow( sqrt( pow( x, 2) + pow( y, 2)), 2))));
    Vector light( x, y, l_x, l_y, z_c, l_z);
    Vector normal( x, y, 0, 0, z_c, 0);
    double angle = getAngle( light, normal);
    uint8_t intense = uint8_t( 255 * angle);
    // printf( "%f %d\n", angle, intense);
    // getchar();

    return sf::Color( intense, 100, 0, 255);
}

bool Sphere::isInside( int x, int y)
{
    x -= width_  / 2;
    y -= height_ / 2;

    return pow( x, 2) + pow( y, 2) <= pow( radius_, 2);
}
