#ifndef WINDOW_FUNCTIONS
#define WINDOW_FUNCTIONS

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

struct WindowData : public sf::Window
{
    sf::RenderWindow window;
    sf::VertexArray pixels;
    unsigned int height;
    unsigned int width;

    sf::Vertex *lines;
    size_t num_of_lines;

    WindowData( unsigned int init_width, unsigned init_height);
    ~WindowData();
};

void drawLines( WindowData *data);

#endif // WINDOW_FUNCTIONS
