#include "buttons.hpp"
#include "abutton.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cassert>
#include <vector>
#include "buttons_img.hpp"

const unsigned int RADIUS_STEP = 10;
const int COORDINATES_STEP = 10;
const uint8_t COLOR_STEP = 10;

Button::Button( const ButtonData &init_data, ButtonId init_id, Sphere *sphere_ptr)
    :   AButton( init_data.pos_x, init_data.pos_y),
        state_( Normal_), id_( init_id), light_ind( 0), sphere_( sphere_ptr), data_( init_data),
        clearShape_( sf::Vector2f( float( init_data.width), float( init_data.height)))
{
    assert( sphere_ptr );

    sprites_  = new sf::Sprite[NUMBER_OF_ICONS];
    textures_ = new sf::Texture[NUMBER_OF_ICONS];

    clearShape_.setPosition( float( init_data.pos_x), float( init_data.pos_y));
    clearShape_.setFillColor( sf::Color::Black);
    setSprites();
}


Button::~Button()
{
    delete [] sprites_;
    delete [] textures_;
}

void Button::setSprites()
{
    const char **icons = nullptr;
    switch ( this->id_ )
    {
        case ButtonPlus:
            icons = ICONS_PLUS;
            break;
        case ButtonMinus:
            icons = ICONS_MINUS;
            break;
        case ButtonDownArrow:
             icons = DOWN_ARROW;
            break;
        case ButtonUpArrow:
             icons = UP_ARROW;
            break;
        case ButtonRightArrow:
             icons = RIGHT_ARROW;
            break;
        case ButtonLeftArrow:
             icons = LEFT_ARROW;
            break;
        case ButtonForwardArrow:
             icons = FORWARD_ARROW;
            break;
        case ButtonBackwardArrow:
             icons = BACKWARD_ARROW;
            break;
        case ButtonRedColor:
             icons = RED_COLOR;
            break;
        case ButtonGreenColor:
             icons = GREEN_COLOR;
            break;
        case ButtonBlueColor:
             icons = BLUE_COLOR;
            break;
        default:
            assert( 0 && "This case is unreachable");
    }
    for ( size_t i = 0; i < NUMBER_OF_ICONS; i++ )
    {
        textures_[i].loadFromFile( icons[i]);
        sprites_ [i].setTexture  ( textures_[i]);
        sprites_ [i].setPosition( this->data_.pos_x, this->data_.pos_y);
    }
}


sf::Sprite &Button::getCurSprite()
{
    return sprites_[state_];
}


void Button::setState( States new_state)
{
    state_ = new_state;
}

bool Button::isOnFocus( sf::Vector2i mouse_pos)
{
    return data_.pos_x <= mouse_pos.x && mouse_pos.x <= data_.pos_x + data_.width &&
            data_.pos_y <= mouse_pos.y && mouse_pos.y <= data_.pos_y + data_.height;
}

void Button::onHover( sf::Vector2i mouse_pos, sf::Event *event, sf::Keyboard *key)
{
    assert( event );
    assert( key );

    if ( isOnFocus( mouse_pos) )
    {
        this->setState( OnHover_);
    } else
    {
        this->setState( Normal_);
    }
}

void Button::onClick( sf::Vector2i mouse_pos, sf::Event *event, sf::Keyboard *key)
{
    assert( event );
    assert( key );

    if ( !isOnFocus( mouse_pos) )
    {
        this->setState( Normal_);
        return;
    }
    this->setState( Clicked_);
    sphere_->setChangeStatus( true);
    std::vector<LightPointData> data = sphere_->getLight();

    int8_t color_f = ( key->isKeyPressed( sf::Keyboard::A ) ) ? -1 : 1;

                                                    size_t l_ind = 0;
    if      ( key->isKeyPressed( sf::Keyboard::LAlt    ) ) l_ind = 1;
    else if ( key->isKeyPressed( sf::Keyboard::LControl) ) l_ind = 2;

    switch ( this->id_ )
    {
        case ButtonPlus:
            sphere_->setRadius( sphere_->getRadius() + RADIUS_STEP);
            break;

        case ButtonMinus:
            sphere_->setRadius( sphere_->getRadius() - RADIUS_STEP);
            break;

        case ButtonDownArrow:
            sphere_->setNewLightCoordinate( l_ind, CoordY, sphere_->getLightCoordinate( l_ind, CoordY) - COORDINATES_STEP);
            break;

        case ButtonUpArrow:
            sphere_->setNewLightCoordinate( l_ind, CoordY, sphere_->getLightCoordinate( l_ind, CoordY) + COORDINATES_STEP);
            break;

        case ButtonLeftArrow:
            sphere_->setNewLightCoordinate( l_ind, CoordX, sphere_->getLightCoordinate( l_ind, CoordX) - COORDINATES_STEP);
            break;

        case ButtonRightArrow:
            sphere_->setNewLightCoordinate( l_ind, CoordX, sphere_->getLightCoordinate( l_ind, CoordX) + COORDINATES_STEP);
            break;

        case ButtonForwardArrow:
            sphere_->setNewLightCoordinate( l_ind, CoordZ, sphere_->getLightCoordinate( l_ind, CoordZ) + COORDINATES_STEP);
            break;

        case ButtonBackwardArrow:
            sphere_->setNewLightCoordinate( l_ind, CoordZ, sphere_->getLightCoordinate( l_ind, CoordZ) - COORDINATES_STEP);
            break;

        case ButtonRedColor:
            sphere_->setColorAttribute( l_ind, ColorRed,   uint8_t( (int) data[l_ind].color.getColor().r + COLOR_STEP * color_f));
            break;

        case ButtonGreenColor:
            sphere_->setColorAttribute( l_ind, ColorGreen, uint8_t( (int) data[l_ind].color.getColor().g + COLOR_STEP * color_f));
            break;

        case ButtonBlueColor:
            sphere_->setColorAttribute( l_ind, ColorBlue,  uint8_t( (int) data[l_ind].color.getColor().b + COLOR_STEP * color_f));
            break;

        default:
            assert( 0 && "This case is unreachable" );
    }
}

void Button::onRelease( sf::Vector2i mouse_pos, sf::Event *event, sf::Keyboard *key)
{
    assert( event );
    assert( key );

    if ( !isOnFocus( mouse_pos) )
        return;
    this->setState( Released_);
}

void createButtons( ButtonsManager &manager, Sphere *sphere)
{
    Button *plus_button = new Button( {0, 0, 64, 64}, ButtonPlus, sphere);
    manager.addButton( plus_button);

    Button *minus_button = new Button( {64, 0, 64, 64}, ButtonMinus, sphere);
    manager.addButton( minus_button);

    Button *up_arrow = new Button( {128, 0, 64, 64}, ButtonUpArrow, sphere);
    manager.addButton( up_arrow);

    Button *down_arrow = new Button( {192, 0, 64, 64}, ButtonDownArrow, sphere);
    manager.addButton( down_arrow);

    Button *left_arrow = new Button( {256, 0, 64, 64}, ButtonLeftArrow, sphere);
    manager.addButton( left_arrow);

    Button *right_arrow = new Button( {320, 0, 64, 64}, ButtonRightArrow, sphere);
    manager.addButton( right_arrow);

    Button *forward_arrow = new Button( {384, 0, 64, 64}, ButtonForwardArrow, sphere);
    manager.addButton( forward_arrow);

    Button *backward_arrow = new Button( {448, 0, 64, 64}, ButtonBackwardArrow, sphere);
    manager.addButton( backward_arrow);

    Button *red_color = new Button( {512, 0, 64, 64}, ButtonRedColor, sphere);
    manager.addButton( red_color);

    Button *green_color = new Button( {576, 0, 64, 64}, ButtonGreenColor, sphere);
    manager.addButton( green_color);

    Button *blue_color = new Button( {640, 0, 64, 64}, ButtonBlueColor, sphere);
    manager.addButton( blue_color);
}


sf::RectangleShape &Button::getClearShape()
{
    return clearShape_;
}


void Button::setLightInd( size_t ind)
{
    light_ind = ind;
}
