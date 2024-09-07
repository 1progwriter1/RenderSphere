#include "sphere.h"
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

void Sphere::setPixels( sf::Color inside, sf::Color outside)
{
    for ( size_t y = 0; y < height_; y++ )
    {
        for ( size_t x = 0; x < width_; x++ )
        {
            size_t index = y * width_ + x;
            pixels_[index].position = sf::Vector2f( float( x), float( y));
            pixels_[index].color = isInside( int( x), int( y)) ? inside : outside;
        }
    }
}

bool Sphere::isInside( int x, int y)
{
    x -= width_  / 2;
    y -= height_ / 2;

    return pow( x, 2) + pow( y, 2) <= pow( radius_, 2);
}
