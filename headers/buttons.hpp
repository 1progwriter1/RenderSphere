#ifndef BUTTONS_FUNCTIONS
#define BUTTONS_FUNCTIONS


#include "sphere.hpp"
#include "abutton.hpp"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include "buttons_manager.hpp"


enum ButtonId
{
    ButtonPlus  = 0,
    ButtonMinus = 1,
    ButtonUpArrow = 2,
    ButtonDownArrow = 3,
    ButtonLeftArrow = 4,
    ButtonRightArrow = 5,
    ButtonForwardArrow = 6,
    ButtonBackwardArrow = 7,
    ButtonRedColor = 8,
    ButtonBlueColor = 9,
    ButtonGreenColor = 10,
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

    size_t light_ind;

    sf::Sprite *sprites_;
    sf::Texture *textures_;

    Sphere *sphere_;

    ButtonData data_;

    sf::RectangleShape clearShape_;

public:
    Button( const ButtonData &init_data, ButtonId init_id, Sphere *sphere_ptr);
    ~Button();


    sf::Sprite &getCurSprite();
    States getState() const;
    void setState( States new_state);

    bool isOnFocus( sf::Vector2i mouse_pos);

    void setChangeStatus( bool new_status);
    bool isSphereChanged();

    sf::RectangleShape &getClearShape();

    void onClick  ( sf::Vector2i mouse_pos, sf::Event *event, sf::Keyboard *key);
    void onHover  ( sf::Vector2i mouse_pos, sf::Event *event, sf::Keyboard *key);
    void onRelease( sf::Vector2i mouse_pos, sf::Event *event, sf::Keyboard *key);

    void setLightInd( size_t ind);

private:
    void setSprites();
};

void createButtons( ButtonsManager &manager, Sphere *sphere);

#endif // BUTTONS_FUNCTIONS
