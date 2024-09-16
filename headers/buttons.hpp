#ifndef BUTTONS_FUNCTIONS
#define BUTTONS_FUNCTIONS

#include "graphlib.hpp"
#include "sphere.hpp"
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

struct ButtonData
{
    float position_x_;
    float position_y_;
    float width;
    float height;
};

class Button : public AButton
{
    States state_;

    sf::Sprite *sprites_;
    sf::Texture *textures_;
    Sphere *sphere;
    const size_t NUMBER_OF_SPRITES = 4;

    ButtonData data_;

public:
    void (*execute)( Sphere &sphere);

public:
    Button( const ButtonData &init_data, const char **pictures, size_t num_of_pic, Sphere *sphere);
    ~Button();
    sf::Sprite &getCurSprite();

    States getState() const;
    void setState( States new_state);

    bool isOnFocus( sf::Vector2i mouse_pos);
};

class ButtonsManager
{
    std::vector<Button *> buttons_;

public:
    ButtonsManager();
    ~ButtonsManager();

    void addButton( const ButtonData &init_data, const char **pictures, size_t num_of_pic, void (*execute_func)( Sphere &sphere));
    void proceedButtons( GraphWindow &window, sf::Event &event, Sphere &sphere);
    void drawButtons( GraphWindow &window);
    void initButtons();
};


void executePlus( Sphere &sphere);
void executeMinus( Sphere &sphere);

#endif // BUTTONS_FUNCTIONS
