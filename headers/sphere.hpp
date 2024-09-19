#ifndef SPHERE_DRAW_FUNCTIONS
#define SPHERE_DRAW_FUNCTIONS

#include "coor_sys.hpp"
#include "color.hpp"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

enum CoordNames
{
    CoordX = 0,
    CoordY = 1,
    CoordZ = 2,
};

struct LightPointData
{
    int x;
    int y;
    int z;
    Color color;
};

struct Coordinates3d
{
    int x;
    int y;
    int z;
};

class Sphere : sf::VertexArray
{
private:
    sf::VertexArray pixels_;

    unsigned int width_;
    unsigned int height_;
    unsigned int radius_;

    Coordinates3d view_pos_;

    std::vector<LightPointData> light_;

    bool is_changed_;

public:
    Sphere( unsigned int init_radius, unsigned int init_width, unsigned int init_height);
    ~Sphere();

    sf::VertexArray &getPixels();
    Coordinates3d getViewPos() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    const std::vector<LightPointData> &getLight() const;
    const sf::Sprite &getSprite( size_t index);

    unsigned int getRadius() const;
    void setRadius( unsigned int new_radius);

    bool isChanged();
    void setChangeStatus( bool new_status);

    int getZOnSphere( const PointCoordinates &point) const;
    void setPixels( CoordinateSys *c_sys);
    bool isInside( const PointCoordinates &point) const;

    void setNewLightCoordinate( size_t light_ind, CoordNames coord, int new_value);
    int getLightCoordinate( size_t light_ind, CoordNames coord);
};

Color getColor( const Sphere &sphere, const PointCoordinates &point);
Color getLambertColor( const Sphere &sphere, const PointCoordinates &point);
Color getBlick( const Sphere &sphere, const PointCoordinates &point);

#endif // SPHERE_DRAW_FUNCTIONS
