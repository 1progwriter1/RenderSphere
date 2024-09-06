#include <cstdio>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "coor_sys.h"
#include "graphlib.h"
#include "sphere.h"

int main()
{
    GraphWindow window( 800, 600);
    Sphere sphere( 200, 800, 600);
    sphere.setPixels( sf::Color::White, sf::Color::White);

    std::vector<float> vec;
    for (const int& i : vec) {

    }
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

        window.drawPixels( sphere.pixels_);
    }
//     CoordinateSys c_sys( 800, 600);
//
//     while ( data.window.isOpen() )
//     {
//         sf::Event event;
//         while (data.window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 data.window.close();
//         }
//         updateLines( &data, &c_sys);
//
//         drawLines( &data);
//     }

    return 0;
}


