#ifndef SPHERE_DRAW_FUNCTIONS
#define SPHERE_DRAW_FUNCTIONS

#include "buttons.hpp"
#include "coor_sys.hpp"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

struct LightPointData
{
    int x;
    int y;
    int z;
    sf::Color color;
    sf::Color blick;
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
    std::vector<Button> buttons_;

public:
    Sphere( unsigned int init_radius, unsigned int init_width, unsigned int init_height);
    ~Sphere();

    sf::VertexArray &getPixels();
    Coordinates3d getViewPos() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned int getRadius() const;
    const std::vector<LightPointData> &getLight() const;
    const sf::Sprite &getSprite( size_t index);

    void addButton( const Button &button);
    void setRadius( unsigned int new_radius);

    int getZOnSphere( const PointCoordinates &point) const;
    void setPixels( CoordinateSys *c_sys);
    bool isInside( const PointCoordinates &point) const;
};

sf::Color getColor( const Sphere &sphere, const PointCoordinates &point);
sf::Color getLambertColor( const Sphere &sphere, const PointCoordinates &point);
sf::Color getBlick( const Sphere &sphere, const PointCoordinates &point);
void mulColor( sf::Color &color, double angle);
sf::Color blendolors( const sf::Color &color_1);

void createButtons( Sphere &sphere);

#endif // SPHERE_DRAW_FUNCTIONS
