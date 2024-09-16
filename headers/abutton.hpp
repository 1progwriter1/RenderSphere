#ifndef ABSTRACT_BUTTON_FUNC
#define ABSTRACT_BUTTON_FUNC

#include <SFML/Graphics.hpp>

class AButton
{
    int x_;
    int y_;

public:
    AButton( int init_x, int init_y);
    virtual ~AButton() = default;

    virtual void onClick  ( sf::Vector2i mouse_pos) = 0;
    virtual void onHover  ( sf::Vector2i mouse_pos) = 0;
    virtual void onRelease( sf::Vector2i mouse_pos) = 0;

protected:
    int getX() const;
    int getY() const;
};

#endif // ABSTRACT_BUTTON_FUNC
