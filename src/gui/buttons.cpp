#include "buttons.hpp"
#include <cassert>

Button::Button( const char *file, float init_x_pos, float init_y_pos)
{
    assert( file);

    texture_.loadFromFile( file);
    sprite_.setTexture( texture_);

    position_x_ = init_x_pos;
    position_y_ = init_y_pos;

    sprite_.setPosition( position_x_, position_y_);
}

const sf::Sprite &Button::getSprite() const
{
    return sprite_;
}
