#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "clock.h"
#include "graphlib.h"
#include "sphere.h"

#include "../../MyLibraries/headers/systemdata.h"

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

    GraphWindow window( 800, 600);
    Sphere sphere( 200, 800, 600);

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
        sphere.setPixels( &window.c_sys_);

        window.drawPixels( sphere.getPixels());
    }

    return SUCCESS;
}


