#ifndef VECTOR_CLOCK
#define VECTOR_CLOCK

#include "coor_sys.h"
#include <SFML/Graphics.hpp>

class Clock : sf::Vertex
{
    sf::Vertex lines;

    int x_center_;
    int y_center_;
    int sec_arrow_len_;

public:
    Clock( int init_arrow_length, int init_x_center = 0, int init_y_center = 0);
    ~Clock();
};

void updateClock( CoordinateSys *c_sys);

#endif // VECTOR_CLOCK
