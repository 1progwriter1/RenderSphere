#include "buttons_manager.hpp"
#include "abutton.hpp"
#include <cassert>
#include <cstddef>


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


void ButtonsManager::addButton( AButton *new_button)
{
    assert( new_button );

    buttons_.push_back( new_button);
}


void ButtonsManager::drawButtons( GraphWindow *window)
{
    assert( window );

    size_t size = buttons_.size();
    for ( size_t i = 0; i < size; i++ )
    {
        window->drawSprite( buttons_[i]->getCurSprite());
    }
}


void ButtonsManager::proceedButtons( GraphWindow *window, sf::Event *event, sf::Keyboard *key, Sphere *sphere)
{
    assert( window );
    assert( event );
    assert( sphere );
    assert( key );

    size_t size = buttons_.size();
    if ( event->type == sf::Event::MouseButtonPressed )
    {
        for ( size_t i = 0; i < size; i++ )
        {
            buttons_[i]->onClick( sf::Mouse::getPosition( window->window_), event, key);
        }
    } else
    {
        for ( size_t i = 0; i < size; i++ )
        {
            buttons_[i]->onHover( sf::Mouse::getPosition( window->window_), event, key);
        }
    }
}
