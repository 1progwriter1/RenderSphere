#ifndef BUTTONS_MANAGER
#define BUTTONS_MANAGER

#include "abutton.hpp"
#include "graphlib.hpp"
#include "sphere.hpp"
#include <vector>

class ButtonsManager
{
    std::vector<AButton *> buttons_;

public:
    ButtonsManager()  = default;
    ~ButtonsManager();

    void addButton( AButton *new_button);
    void drawButtons( GraphWindow *window);

    void proceedButtons( GraphWindow *window, sf::Event *event, Sphere *sphere);
};

#endif // BUTTONS_MANAGER
