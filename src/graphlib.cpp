#include "graphlib.hpp"
#include "coor_sys.hpp"
#include <cstddef>
#include <sys/_types/_size_t.h>
#include <vector>
#include <assert.h>

GraphWindow::GraphWindow( unsigned int init_width, unsigned int init_height, const char *label)
    : window_( sf::VideoMode( init_width, init_height), label), c_sys_( (int) init_width, (int) init_height)
{
    height_ = init_height;
    width_ = init_width;
}

GraphWindow::~GraphWindow()
{
    height_ = 0;
    width_ = 0;
}

void GraphWindow::drawLines( sf::Vertex *lines, size_t size)
{
    assert( lines);

    window_.clear( sf::Color::Black);
    window_.draw( lines, size, sf::Lines);
    window_.display();
}

void GraphWindow::drawPixels( sf::VertexArray &pixels)
{
    window_.clear( sf::Color::Black);
    window_.draw( pixels);
    window_.display();
}

void GraphWindow::drawSprites( std::vector<sf::Sprite> &sprites)
{
    size_t number = sprites.size();
    for ( size_t i = 0; i < number; i++ )
    {
        window_.draw( sprites.data()[i]);
    }
}
