#include "sphere.hpp"
#include "coor_sys.hpp"
#include "vector.hpp"
#include <_types/_uint8_t.h>
#include <cassert>
#include <cstddef>
#include <vector>

const sf::Color BACKGROUND_COLOR = sf::Color::Black;
const sf::Color DEFAULT_COLOR = sf::Color::Black;
const sf::Color AMBIENT_COLOR = sf::Color( 50, 75, 100, 255);

Sphere::Sphere( unsigned int init_radius, unsigned int init_width, unsigned int init_height)
    :   pixels_( sf::Points, init_width * init_height),
        width_( init_width), height_( init_height), radius_( init_radius), is_changed_( true)
{
    light_.push_back( {  300, -150, 250, Color( 150, 0, 0, 255)});
    light_.push_back( {-600,   0,    0, Color( 0, 150, 0, 255)});
    light_.push_back( { 500,  500, 500, Color( 100, 100, 100, 255)});

    view_pos_ = { 0, 0, 500};
}


Sphere::~Sphere()
{

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
            pixels_[index].color = getColor( *this, point).getColor();
        }
    }
}


Color getColor( const Sphere &sphere, const PointCoordinates &point)
{

    if ( !sphere.isInside( point) )
    {
        return BACKGROUND_COLOR;
    }
    Color color = Color( DEFAULT_COLOR) * Color( AMBIENT_COLOR);
    color = color + getLambertColor( sphere, point);
    color = color + getBlick( sphere, point);

    return color;
}


Color getLambertColor( const Sphere &sphere, const PointCoordinates &point)
{
    Color color( 0, 0, 0, 255);
    std::vector<LightPointData> lightData = sphere.getLight();

    int z_c = sphere.getZOnSphere( point);
    Vector normal( point.x, point.y, 0, 0, z_c, 0);

    size_t num_of_lights = lightData.size();
    for ( size_t i = 0; i < num_of_lights; i++ )
    {
        Vector light( lightData.data()[i].x, lightData.data()[i].y, point.x, point.y, lightData.data()[i].z, z_c);

        double angle = getAngle( light, normal);
        if ( angle < 0 ) angle = 0;

        Color cur( lightData.data()[i].color);

        cur = cur * angle;

        color = color + cur;
    }
    return color;
}


Color getBlick( const Sphere &sphere, const PointCoordinates &point)
{
    Coordinates3d view_pos = sphere.getViewPos();

    int z_c = sphere.getZOnSphere( point);
    Vector view( point.x, point.y, view_pos.x, view_pos.y, z_c, view_pos.z);
    Vector normal( point.x, point.y, 0, 0, z_c, 0);

    Color color( 0, 0, 0, 255);
    std::vector<LightPointData> lightData = sphere.getLight();

    size_t num_of_lights = lightData.size();
    for ( size_t i = 0; i < num_of_lights; i++ )
    {
        Vector light( lightData.data()[i].x, lightData.data()[i].y, point.x, point.y, lightData.data()[i].z, z_c);
        Vector reflected = light.reflectNormal( normal);

        double angle = pow( getAngle( reflected, view), 30); // magical constant))))
        if ( angle < 0 ) angle = 0;

        Color cur( lightData.data()[i].color);

        cur = cur * angle;

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


void Sphere::setRadius( unsigned int new_radius)
{
    if ( new_radius <= 0 )  return;
    radius_ = new_radius;
}


bool Sphere::isChanged()
{
    return is_changed_;
}


void Sphere::setChangeStatus( bool new_status)
{
    is_changed_ = new_status;
}


void Sphere::setNewLightCoordinate( size_t light_ind, CoordNames coord, int new_value)
{
    switch( coord )
    {
        case CoordX:
            light_[(size_t)light_ind].x = new_value;
            break;
        case CoordY:
            light_[(size_t)light_ind].y = new_value;
            break;
        case CoordZ:
            light_[(size_t)light_ind].z = new_value;

    }
}


int Sphere::getLightCoordinate( size_t light_ind, CoordNames coord)
{
    switch( coord )
    {
        case CoordX:
            return light_[(size_t)light_ind].x;
            break;
        case CoordY:
            return light_[(size_t)light_ind].y;
            break;
        case CoordZ:
            return light_[(size_t)light_ind].z;
            break;
        default:
            assert( 0);
    }
}
