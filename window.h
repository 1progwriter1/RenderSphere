#ifndef WINDOW_FUNCTIONS
#define WINDOW_FUNCTIONS

#include <SFML/Graphics.hpp>
#include "vector.h"
#include <vector>

struct WindowData : public sf::Window
{
    sf::RenderWindow window;
    sf::VertexArray pixels;
    unsigned int height;
    unsigned int width;

    WindowData( unsigned int init_width, unsigned init_height);
    ~WindowData();
};

void drawVector( Vector vec);

#endif // WINDOW_FUNCTIONS
