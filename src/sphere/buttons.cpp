#include "buttons.hpp"
#include "abutton.hpp"
#include "sphere.hpp"
#include <cassert>
#include <cstddef>
#include <cstdio>

const size_t NUMBER_OF_ICONS = 4;
// icons: Normal_, OnHover_, Clicked_, Released_
const char *ICONS_PLUS[NUMBER_OF_ICONS] =
{
    "images/plusNormal.png", "images/plusOnHover.png", "images/plusPressed.png", "images/plusNormal.png"
};
const char *ICONS_MINUS[NUMBER_OF_ICONS] =
{
    "images/minusNormal.png", "images/minusOnHover.png", "images/minusPressed.png", "images/minusNormal.png"
};

const unsigned int RADIUS_STEP = 10;

Button::Button( const ButtonData &init_data, ButtonId init_id, Sphere *sphere_ptr)
    :   AButton( init_data.pos_x, init_data.pos_y),
        state_( Normal_), id_( init_id), sphere_( sphere_ptr), data_( init_data)
{
    assert( sphere_ptr );

    sprites_  = new sf::Sprite[NUMBER_OF_SPRITES];
    textures_ = new sf::Texture[NUMBER_OF_SPRITES];

}


Button::~Button()
{
    delete [] sprites_;
    delete [] textures_;
}

void Button::setSprites( int pos_x, int pos_y)
{
    const char **icons = nullptr;
    switch ( this->id_ )
    {
        case ButtonPlus:
            icons = ICONS_PLUS;
            break;
        case ButtonMinus:
            icons = ICONS_MINUS;
            break;
        default:
            assert( 0 && "This case is unreachable");
    }
    for ( size_t i = 0; i < NUMBER_OF_ICONS; i++ )
    {
        textures_[i].loadFromFile( icons[i]);
        sprites_ [i].setTexture  ( textures_[i]);
        sprites_ [i].setPosition( pos_x, pos_y);
    }
}


sf::Sprite &Button::getCurSprite()
{
    return sprites_[state_];
}


void Button::setState( States new_state)
{
    state_ = new_state;
}

bool Button::isOnFocus( sf::Vector2i mouse_pos)
{
    return data_.pos_x <= mouse_pos.x && mouse_pos.x <= data_.pos_x + data_.width &&
            data_.pos_y <= mouse_pos.y && mouse_pos.y <= data_.pos_y + data_.height;
}

void Button::onHover( sf::Vector2i mouse_pos)
{
    if ( isOnFocus( mouse_pos) )
    {
        this->setState( OnHover_);
    }
}

void Button::onClick( sf::Vector2i mouse_pos)
{
    if ( !isOnFocus( mouse_pos) )
        return;
    this->setState( Clicked_);

    switch ( this->id_ )
    {
        case ButtonPlus:
            sphere_->setRadius( sphere_->getRadius() + RADIUS_STEP);
            break;

        case ButtonMinus:
            sphere_->setRadius( sphere_->getRadius() - RADIUS_STEP);
            break;

        default:
            assert( 0 && "This case is unreachable" );
    }
}

void Button::onRelease( sf::Vector2i mouse_pos)
{
    if ( !isOnFocus( mouse_pos) )
        return;
    this->setState( Released_);
}
