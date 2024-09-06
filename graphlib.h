#ifndef GRAPH_LIB_FUNCTIONS
#define GRAPH_LIB_FUNCTIONS

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

class GraphWindow : public sf::Window
{
public:
    sf::RenderWindow window_;

    unsigned int height_;
    unsigned int width_;

public:
    GraphWindow( unsigned int init_width, unsigned init_height, const char *label = "hello");
    ~GraphWindow();
    void drawLines( sf::Vertex *line, size_t size);
    void drawPixels( sf::VertexArray &pixels);
};

#endif // GRAPH_LIB_FUNCTIONS
