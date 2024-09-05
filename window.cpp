#include "window.h"
#include "vector.h"
#include <cstddef>

WindowData::WindowData( unsigned int init_width, unsigned int init_height)
    : window( sf::VideoMode( init_width, init_height), "Hello world"), pixels( sf::Points, init_width * init_height), data( 10)
{
    height = init_height;
    width = init_width;
}

WindowData::~WindowData()
{
    height = 0;
    width = 0;
}

void drawVectors( WindowData *data, Vector vec)
{
    for ( size_t i = 0; ; i++ )
    {
        Coordinates points = vec.getCoordinates();

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(points.x_0, points.y_0)),
            sf::Vertex(sf::Vector2f(points.x, points.y))
        }
    }
}

void addVector(WindowData *data, Vector vec)
{
    data->data.push_back( vec);
}
