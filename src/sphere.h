#ifndef SPHERE_DRAW_FUNCTIONS
#define SPHERE_DRAW_FUNCTIONS

#include <SFML/Graphics.hpp>
#include <cstddef>

class Sphere : sf::VertexArray
{
public:
    sf::VertexArray pixels_;
private:
    unsigned int width_;
    unsigned int height_;
    unsigned int radius_;
    unsigned int length_;

public:
    Sphere( unsigned int init_radius, unsigned int init_width, unsigned int init_height);
    ~Sphere();
    void setPixels( sf::Color inside = sf::Color::Red, sf::Color outside = sf::Color(0, 255, 0, 12));

private:
    bool isInside( int x, int y);
};

#endif // SPHERE_DRAW_FUNCTIONS
