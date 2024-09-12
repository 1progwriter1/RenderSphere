#include "color.hpp"

Color::Color( sf::Color init_color)
    :   color_( init_color)
{

}

Color Color::operator* ( const Color &color)
{
    uint8_t r = uint8_t( std::min( uint16_t( this->color_.r * color.color_.r), uint16_t( 255)));
    uint8_t g = uint8_t( std::min( uint16_t( this->color_.g * color.color_.g), uint16_t( 255)));
    uint8_t b = uint8_t( std::min( uint16_t( this->color_.b * color.color_.b), uint16_t( 255)));

    return Color( sf::Color( r, g, b, std::max( this->color_.a, color.color_.a)));;
}

Color Color::operator+ ( const Color &color)
{
    uint8_t r = uint8_t( std::min( uint16_t( this->color_.r + color.color_.r), uint16_t( 255)));
    uint8_t g = uint8_t( std::min( uint16_t( this->color_.g + color.color_.g), uint16_t( 255)));
    uint8_t b = uint8_t( std::min( uint16_t( this->color_.b + color.color_.b), uint16_t( 255)));

    return Color( sf::Color( r, g, b, std::max( this->color_.a, color.color_.a)));;
}

Color Color::operator* ( const double cf)
{
    uint8_t r = uint8_t( std::min( uint16_t( this->color_.r * cf), uint16_t( 255)));
    uint8_t g = uint8_t( std::min( uint16_t( this->color_.g * cf), uint16_t( 255)));
    uint8_t b = uint8_t( std::min( uint16_t( this->color_.b * cf), uint16_t( 255)));

    return Color( sf::Color( r, g, b, this->color_.a));
}

