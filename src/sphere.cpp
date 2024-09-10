#include "sphere.h"
#include <cassert>
#include <cmath>
#include <cstddef>

Sphere::Sphere( unsigned int init_radius, unsigned int init_width, unsigned int init_height)
    : pixels_( sf::Points, init_width * init_height)
{
    radius_ = init_radius;
    width_  = init_width;
    height_ = init_height;

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
                color = zColor( int( x), int( y));
            } else
            {
                color = sf::Color( 0, 100, 0, 255);
            }
            pixels_[index].color = color;
        }
    }
}

sf::Color Sphere::zColor( int x, int y)
{
    x -= width_  / 2;
    y -= height_ / 2;
    double part = sqrt( pow( x, 2) + pow( y, 2)) / radius_;

    return sf::Color( uint8_t( 255 - 255 * part), 0, 0, 255);
}

bool Sphere::isInside( int x, int y)
{
    x -= width_  / 2;
    y -= height_ / 2;

    return pow( x, 2) + pow( y, 2) <= pow( radius_, 2);
}
