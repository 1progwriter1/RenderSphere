#include "window.h"
#include <cstddef>
#include <vector>

WindowData::WindowData( unsigned int init_width, unsigned int init_height)
    : window( sf::VideoMode( init_width, init_height), "")
{
    height = init_height;
    width = init_width;

    lines = NULL;
    num_of_lines = 0;
}

WindowData::~WindowData()
{
    height = 0;
    width = 0;

    if ( num_of_lines != 0 )
    {
        delete [] lines;
    }
}

void drawLines( WindowData *data)
{
    data->window.clear( sf::Color::Black);
    data->window.draw( data->lines, data->num_of_lines, sf::Lines);
    data->window.display();
}

