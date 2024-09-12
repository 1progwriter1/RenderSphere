#ifndef COLOR_FUNCTIONS
#define COLOR_FUNCTIONS

#include "vector.hpp"
#include <SFML/Graphics.hpp>

class Color
{
    sf::Color color_;

public:
    Color( sf::Color init_color);
    ~Color() {};
    sf::Color &getColor() const;

    Color operator* ( const Color &color);
    Color operator+ ( const Color &color);
    Color operator* ( const double cf);
};

#endif //  COLOR_FUNCTIONS
