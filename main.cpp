#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "coor_sys.h"
#include "vector.h"
#include "clock.h"
#include "window.h"

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

        sf::Vertex lines[6];
        createArrows( lines, c_sys);

        data.window.clear( sf::Color::Black);
        data.window.draw(lines, 6, sf::Lines);
        data.window.display();

        //updateClock();
    }

    //destroyClock();

    return 0;
}


