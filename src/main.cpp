#include <cstdio>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "buttons.hpp"
#include "clock.hpp"
#include "graphlib.hpp"
#include "sphere.hpp"

#include "../../MyLibraries/headers/systemdata.h"
#include "vector.hpp"

// добавить функторы

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

//     Vector normal( 0, 7, 0, 0, 5, 0);
//     Vector light( -10, 14, 0, 0, 10, 0);
//     Vector reflected = light.reflectNormal( normal);
//
//     fprintf( stderr, "%f %f %f %f %f %f\n", reflected.getCoordinates().x, reflected.getCoordinates().y, reflected.getCoordinates().z,
//                                                     reflected.getCoordinates().x_0, reflected.getCoordinates().y_0, reflected.getCoordinates().z_0);
//             fprintf( stderr, "%f %f %f %f %f %f\n", normal.getCoordinates().x, normal.getCoordinates().y, normal.getCoordinates().z,
//                                                     normal.getCoordinates().x_0, normal.getCoordinates().y_0, normal.getCoordinates().z_0);
//             fprintf( stderr, "%f %f %f %f %f %f\n", light.getCoordinates().x, light.getCoordinates().y, light.getCoordinates().z,
//                                                     light.getCoordinates().x_0, light.getCoordinates().y_0, light.getCoordinates().z_0);
//
//     fprintf( stderr, "%f %f %f\n", getAngle( light, normal), getAngle( reflected, normal), getAngle( normal, reflected));

    GraphWindow window( W_WIDTH, W_HEIGHT);
    Sphere sphere( INIT_RADIUS, W_WIDTH, W_HEIGHT);
    ButtonsManager manager;
    createButtons( manager, &sphere);

    while ( window.window_.isOpen() )
    {
        sf::Event event;
        sf::Keyboard key;
        while ( window.window_.pollEvent( event) )
        {
            if ( event.type == sf::Event::Closed )
            {
                window.window_.close();
            }
        }
        if ( sphere.isChanged() )
        {
            sphere.setPixels( &window.c_sys_);
            sphere.setChangeStatus( false);
            window.display();
        }
        window.clear( sf::Color::Black);
        window.drawPixels( sphere.getPixels());

        manager.proceedButtons( &window, &event, &key, &sphere);
        manager.drawButtons( &window);

        window.display();
    }

    return SUCCESS;
}


