#include <cstdio>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "clock.h"
#include "coor_sys.h"
#include "graphlib.h"

int main()
{
//     GraphWindow window( 800, 600);
//     Sphere sphere( 200, 800, 600);
//     sphere.setPixels();
//
//     while ( window.window_.isOpen() )
//     {
//         sf::Event event;
//         while ( window.window_.pollEvent( event) )
//         {
//             if ( event.type == sf::Event::Closed )
//             {
//                 window.window_.close();
//             }
//         }
//
//         window.drawPixels( sphere.pixels_);
//     }
    GraphWindow window( 800, 600);
    Clock clock( 100);

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
        clock.updateClock( &window.c_sys_);

        window.drawLines( clock.lines, clock.NUMBER_OF_POINTS);
    }

    return 0;
}


