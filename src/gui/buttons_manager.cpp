#include "buttons_manager.hpp"
#include "abutton.hpp"
#include "buttons.hpp"
#include <cassert>

ButtonsManager::~ButtonsManager()
{
    size_t size = buttons_.size();
    for ( size_t i = 0; i < size; i++ )
    {
        delete buttons_[i];
    }
}


void ButtonsManager::addButton( AButton *new_button)
{
    assert( new_button );

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
