#include <cassert>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "buttons.hpp"
#include "clock.hpp"
#include "graphlib.hpp"
#include "sphere.hpp"

#include "../../MyLibraries/headers/systemdata.h"

const unsigned int W_HEIGHT = 900;
const unsigned int W_WIDTH = 1400;
const unsigned int INIT_RADIUS = 200;

int main( const int argc, const char *argv[])
{
    if ( argc > 1 )
    {
        if ( strcmp( argv[1], "--clock") == 0 )
        {
            drawClock();
        } else
        {
            printf( RED "error: " END_OF_COLOR "unknow flag: \"%s\"\n", argv[1]);
            return ERROR;
        }
        return SUCCESS;
    }

    GraphWindow window( W_WIDTH, W_HEIGHT);
    Sphere sphere( INIT_RADIUS, W_WIDTH, W_HEIGHT);
    ButtonsManager manager;
    createButtons( manager, &sphere);

    while ( window.window_.isOpen() )
    {
        sf::Event event;
        while ( window.window_.pollEvent( event) )
        {
            if ( event.type == sf::Event::Closed )
            {
                window.window_.close();
            }
        }
        window.clear();

        sphere.setPixels( &window.c_sys_);
        window.drawPixels( sphere.getPixels());

        manager.proceedButtons( &window, &event, &sphere);
        manager.drawButtons( &window);

        window.display();
    }

    return SUCCESS;
}


