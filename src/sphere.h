#ifndef SPHERE_DRAW_FUNCTIONS
#define SPHERE_DRAW_FUNCTIONS

#include <SFML/Graphics.hpp>
#include <cstddef>

struct PointCoordinates3d
{
    int x;
    int y;
    int z;
};

class Sphere : sf::VertexArray
{
public:
    sf::VertexArray pixels_;
private:
    unsigned int width_;
    unsigned int height_;
    unsigned int radius_;
    unsigned int length_;

    PointCoordinates3d light_ = {};

public:
    Sphere( unsigned int init_radius, unsigned int init_width, unsigned int init_height);
    ~Sphere();
    void setPixels();

private:
    bool isInside( int x, int y);
    sf::Color getColor( int x, int y);
};

#endif // SPHERE_DRAW_FUNCTIONS
