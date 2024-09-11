#include "sphere.h"
#include "coor_sys.h"
#include "vector.h"
#include <_types/_uint8_t.h>
#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <ratio>
#include <sys/_types/_size_t.h>
#include <vector>

const sf::Color BACKGROUND_COLOR = sf::Color::Black;
const sf::Color DEFAULT_COLOR = sf::Color( 102, 0, 102, 100);

Sphere::Sphere( unsigned int init_radius, unsigned int init_width, unsigned int init_height)
    : pixels_( sf::Points, init_width * init_height)
{
    radius_ = init_radius;
    width_  = init_width;
    height_ = init_height;

    light_.push_back( { 10, -150, 250, sf::Color( 150, 0, 0, 255), sf::Color( 255, 102, 102, 255)});
    light_.push_back( {-300, 0, 0, sf::Color( 0, 150, 0, 255), sf::Color( 0, 255, 128, 255)});
    light_.push_back( {500, 500, 500, sf::Color( 255, 255, 153, 150), sf::Color( 255, 255, 204, 100)});

    view_pos_ = { 0, 0, 500};
}

Sphere::~Sphere()
{
    radius_ = 0;
    width_  = 0;
    height_ = 0;
}

sf::VertexArray &Sphere::getPixels()
{
    return pixels_;
}

Coordinates3d Sphere::getViewPos() const
{
    return view_pos_;
}
unsigned int Sphere::getWidth() const
{
    return width_;
}
unsigned int Sphere::getHeight() const
{
    return height_;
}
unsigned int Sphere::getRadius() const
{
    return radius_ ;
}

 const std::vector<LightPointData> &Sphere::getLight() const
{
    return light_;
}

void Sphere::setPixels( CoordinateSys *c_sys)
{
    assert( c_sys);

    for ( size_t y = 0; y < height_; y++ )
    {
        for ( size_t x = 0; x < width_; x++ )
        {
            size_t index = y * width_ + x;
            pixels_[index].position = sf::Vector2f( float( x), float( y));

            PointCoordinates point = c_sys->translateFromPixels( {(int) x, (int) y});
            pixels_[index].color = getColor( *this, point);
        }
    }
}

sf::Color getColor( const Sphere &sphere, const PointCoordinates &point)
{

    if ( !sphere.isInside( point) )
    {
        return BACKGROUND_COLOR;
    }
    sf::Color color = DEFAULT_COLOR;
    color = color + getLambertColor( sphere, point);
    color = color + getBlick( sphere, point);

    return color;
}

sf::Color getLambertColor( const Sphere &sphere, const PointCoordinates &point)
{
    sf::Color color( 0, 0, 0, 0);
    std::vector<LightPointData> lightData = sphere.getLight();

    int z_c = sphere.getZOnSphere( point);
    Vector normal( point.x, point.y, 0, 0, z_c, 0);

    size_t num_of_lights = lightData.size();
    for ( size_t i = 0; i < num_of_lights; i++ )
    {
        int l_x = lightData.data()[i].x;
        int l_y = lightData.data()[i].y;
        int l_z = lightData.data()[i].z;
        Vector light( l_x, l_y, point.x, point.y, l_z, z_c);

        double angle = getAngle( light, normal);
        if ( angle < 0 ) angle = 0;

        sf::Color cur = lightData.data()[i].color;

        cur.r = uint8_t( std::round( double( cur.r) * angle));
        cur.g = uint8_t( std::round( double( cur.g) * angle));
        cur.b = uint8_t( std::round( double( cur.b) * angle));
        cur.a = uint8_t( std::round( double (cur.a) * angle));

        color = color + cur;
    }
    return color;
}

sf::Color getBlick( const Sphere &sphere, const PointCoordinates &point)
{
    Coordinates3d view_pos = sphere.getViewPos();

    int z_c = sphere.getZOnSphere( point);
    Vector view( point.x, point.y, view_pos.x, view_pos.y, z_c, view_pos.z);
    Vector normal( point.x, point.y, 0, 0, z_c, 0);

    sf::Color color( 0, 0, 0, 0);
    std::vector<LightPointData> lightData = sphere.getLight();

    size_t num_of_lights = lightData.size();
    for ( size_t i = 0; i < num_of_lights; i++ )
    {
        int l_x = lightData.data()[i].x;
        int l_y = lightData.data()[i].y;
        int l_z = lightData.data()[i].z;
        Vector light( l_x, l_y, point.x, point.y, l_z, z_c);
        Vector reflected = light.reflectNormal( normal);

        double angle = pow( getAngle( reflected, view), 13); // magical constant))))
        if ( angle < 0 ) angle = 0;

        sf::Color cur = lightData.data()[i].blick;

        cur.r = uint8_t( std::round( double( cur.r) * angle));
        cur.g = uint8_t( std::round( double( cur.g) * angle));
        cur.b = uint8_t( std::round( double( cur.b) * angle));
        cur.a = uint8_t( std::round( double (cur.a) * angle));

        color = color + cur;

    }

    return color;
}

bool Sphere::isInside( const PointCoordinates &point) const
{
    return pow( point.x, 2) + pow( point.y, 2) <= pow( radius_, 2);
}

int Sphere::getZOnSphere( const PointCoordinates &point) const
{
    return int( std::round( sqrt( pow( radius_, 2) - pow( sqrt( pow( point.x, 2) + pow( point.y, 2)), 2))));
}
