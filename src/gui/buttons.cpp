#include "buttons.hpp"
#include "graphlib.hpp"
#include <cassert>
#include <cstddef>
#include <sys/_types/_size_t.h>

Button::Button( float init_x_pos, float init_y_pos, const char **pictures, size_t num_of_pic)
    :   state_( Normal_), position_x_( init_x_pos), position_y_( init_y_pos)
{
    assert( pictures);
    assert( num_of_pic >= NUMBER_OF_SPRITES);

    sprites_ = new sf::Sprite[NUMBER_OF_SPRITES];
    textures_ = new sf::Texture[NUMBER_OF_SPRITES];

    for ( size_t i = 0; i < NUMBER_OF_SPRITES; i++ )
    {
        textures_[i].loadFromFile( pictures[i]);
        sprites_[i].setTexture( textures_[i]);
        sprites_->setPosition( init_x_pos, init_y_pos);
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


void ButtonsManager::addButton( float init_x_pos, float init_y_pos, const char **pictures, size_t num_of_pic)
{
    assert( pictures);

    Button *new_button = new Button( init_x_pos, init_y_pos, pictures, num_of_pic);
    buttons_.push_back( new_button);
}


void ButtonsManager::proceedButtons( sf::Event &event)
{
    size_t size = buttons_.size();
    for ( size_t i = 0; i < size; i++ )
    {

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
    const char *plus[] = {"Images/plusNormal.png", "Images/minusNormal.png", "Images/plusPressed.png", "Images/plusNormal.png"};
    addButton( 0, 0, plus, 4);
    const char *minus[] = {"Images/minusNormal.png", "Images/plusNormal.png", "Images/minusPressed.png", "Images/minusNormal.png"};
    addButton( 100, 10, minus, 4);
}
