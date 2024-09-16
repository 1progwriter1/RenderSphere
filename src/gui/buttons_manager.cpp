#include "buttons_manager.hpp"
#include "abutton.hpp"

ButtonsManager::ButtonsManager()
{

}

ButtonsManager::~ButtonsManager()
{

}


void ButtonsManager::addButton(  )
{

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
