#ifndef BUTTONS_FUNCTIONS
#define BUTTONS_FUNCTIONS

#include "graphlib.hpp"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <vector>

enum States
{
    Normal_   = 0,
    OnHover_  = 1,
    Clicked_  = 2,
    Released_ = 3,
};

class Button
{
    States state_;

    sf::Sprite *sprites_;
    sf::Texture *textures_;
    const size_t NUMBER_OF_SPRITES = 4;

    float position_x_;
    float position_y_;

    float width;
    float height;

public:
    Button( float init_x_pos, float init_y_pos, const char **pictures, size_t num_of_pic);
    ~Button();
    sf::Sprite &getCurSprite();

    States getState() const;
    void setState( States new_state);
};

class ButtonsManager
{
    std::vector<Button *> buttons_;

public:
    ButtonsManager();
    ~ButtonsManager();

    void addButton( float init_x_pos, float init_y_pos, const char **pictures, size_t num_of_pic);
    void proceedButtons( sf::Event &event);
    void drawButtons( GraphWindow &window);
    void initButtons();
};

#endif // BUTTONS_FUNCTIONS
