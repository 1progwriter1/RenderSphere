#ifndef BUTTONS_FUNCTIONS
#define BUTTONS_FUNCTIONS

#include <SFML/Graphics.hpp>

class Button
{
    sf::Texture texture_;
    sf::Sprite sprite_;

    float position_x_;
    float position_y_;

public:
    Button( const char *file, float init_x_pos, float init_y_pos);
    ~Button() {};

    const sf::Sprite &getSprite() const;
};

#endif // BUTTONS_FUNCTIONS
