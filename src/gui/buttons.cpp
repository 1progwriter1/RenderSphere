#include "buttons.hpp"
#include "graphlib.hpp"
#include "sphere.hpp"
#include <cassert>
#include <cstddef>
#include <cstdio>

const unsigned int RADIUS_STEP = 10;

Button::Button( const ButtonData &init_data, const char **pictures, size_t num_of_pic, void (*execute_func)( Sphere &sphere))
    :   state_( Normal_), data_( init_data), execute( execute_func)
{
    assert( pictures);
    assert( num_of_pic >= NUMBER_OF_SPRITES);

    sprites_  = new sf::Sprite[NUMBER_OF_SPRITES];
    textures_ = new sf::Texture[NUMBER_OF_SPRITES];

    for ( size_t i = 0; i < NUMBER_OF_SPRITES; i++ )
    {
        textures_[i].loadFromFile( pictures [i]);
        sprites_ [i].setTexture  ( textures_[i]);
        sprites_ [i].setPosition ( init_data.position_x_, init_data.position_y_);
    }
}


Button::~Button()
{
    delete [] sprites_;
    delete [] textures_;
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
    return data_.position_x_ <= mouse_pos.x && mouse_pos.x <= data_.position_x_ + data_.width &&
            data_.position_y_ <= mouse_pos.y && mouse_pos.y <= data_.position_y_ + data_.height;
}

void executeMinus( Sphere &sphere)
{
    sphere.setRadius( sphere.getRadius() - RADIUS_STEP);
}


void executePlus( Sphere &sphere)
{
    sphere.setRadius( sphere.getRadius() + RADIUS_STEP);
}


ButtonsManager::ButtonsManager()
{

}

ButtonsManager::~ButtonsManager()
{
    size_t size = buttons_.size();
    for ( size_t i = 0; i < size; i++ )
    {
        delete buttons_[i];
    }
}


void ButtonsManager::addButton( const ButtonData &init_data, const char **pictures, size_t num_of_pic, void (*execute_func)( Sphere &sphere))
{
    assert( pictures);

    Button *new_button = new Button( init_data, pictures, num_of_pic, execute_func);
    buttons_.push_back( new_button);
}


void ButtonsManager::proceedButtons( GraphWindow &window, sf::Event &event, Sphere &sphere)
{
    size_t size = buttons_.size();

    if ( event.type == sf::Event::MouseButtonPressed )
    {
        for ( size_t i = 0; i < size; i++ )
        {
            if ( buttons_[i]->isOnFocus( sf::Mouse::getPosition( window.window_)))
            {
                buttons_[i]->setState( Clicked_);
                buttons_[i]->execute( sphere);
            }
            else
            {
                buttons_[i]->setState( Normal_);
            }
        }
    }
    else
    {
        for ( size_t i = 0; i < size; i++ )
        {
            if ( buttons_[i]->isOnFocus( sf::Mouse::getPosition( window.window_)))
            {
                buttons_[i]->setState( OnHover_);
            } else
            {
                buttons_[i]->setState( Normal_);
            }
        }
    }
}


void ButtonsManager::drawButtons( GraphWindow &window)
{
    size_t size = buttons_.size();
    for ( size_t i = 0; i < size; i++ )
    {
        window.drawSprite( buttons_[i]->getCurSprite());
    }
}


void ButtonsManager::initButtons()
{
    const char *plus[] = {"images/plusNormal.png", "images/plusOnHover.png", "images/plusPressed.png", "images/plusNormal.png"};
    ButtonData plus_data = { 0, 0, 64, 64};
    addButton( plus_data, plus, 4, executePlus);

    const char *minus[] = {"images/minusNormal.png", "images/minusOnHover.png", "images/minusPressed.png", "images/minusNormal.png"};
    ButtonData minus_data = {64, 0, 64, 64};
    addButton( minus_data, minus, 4, executeMinus);
}
