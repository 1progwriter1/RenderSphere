#include <cstdio>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "coor_sys.h"
#include "graphlib.h"

int main()
{
    WindowData data( 800, 600);
    CoordinateSys c_sys( 800, 600);

    while ( data.window.isOpen() )
    {
        sf::Event event;
        while (data.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                data.window.close();
        }
        updateLines( &data, &c_sys);

        drawLines( &data);
    }

    return 0;
}


