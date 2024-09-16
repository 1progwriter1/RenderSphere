#ifndef BUTTONS_FUNCTIONS
#define BUTTONS_FUNCTIONS

#include "sphere.hpp"
#include "abutton.hpp"
#include <SFML/Graphics.hpp>
#include "buttons_manager.hpp"
#include <cstddef>
#include <vector>

enum ButtonId
{
    ButtonPlus  = 0,
    ButtonMinus = 1,
};

enum States
{
    Normal_   = 0,
    OnHover_  = 1,
    Clicked_  = 2,
    Released_ = 3,
};

struct ButtonData
{
    int pos_x;
    int pos_y;
    float width;
    float height;
};

class Button : public AButton
{
    States state_;

    ButtonId id_;

    sf::Sprite *sprites_;
    sf::Texture *textures_;

    Sphere *sphere_;

    ButtonData data_;

public:
    Button( const ButtonData &init_data, ButtonId init_id, Sphere *sphere_ptr);
    ~Button();


    sf::Sprite &getCurSprite();
    States getState() const;
    void setState( States new_state);

    bool isOnFocus( sf::Vector2i mouse_pos);

    void onClick  ( sf::Vector2i mouse_pos);
    void onHover  ( sf::Vector2i mouse_pos);
    void onRelease( sf::Vector2i mouse_pos);

private:
    void setSprites();
};

void createButtons( ButtonsManager &manager, Sphere *sphere);

#endif // BUTTONS_FUNCTIONS
