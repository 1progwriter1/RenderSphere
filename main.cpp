#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "coor_sys.h"
#include "vector.h"
#include "window.h"

int main()
{
    WindowData data( 800, 400);
    CoordinateSys c_sys( 800, 600);

    initClock();

    while ( data.window.isOpen() )
    {
        sf::Event event;
        while (data.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                data.window.close();
        }

        updateClock();
    }

    destroyClock();

    return 0;
}


