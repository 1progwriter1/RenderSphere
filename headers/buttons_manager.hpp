#ifndef BUTTONS_MANAGER
#define BUTTONS_MANAGER

#include "abutton.hpp"
#include "graphlib.hpp"
#include <vector>

class ButtonsManager
{
    std::vector<AButton *> buttons_;

public:
    ButtonsManager();
    ~ButtonsManager();

    bool needDrawSphere();

    void addButton( AButton *new_button);
    void drawButtons( GraphWindow &window);

    void proceedButtons( GraphWindow *window, sf::Event *event, sf::Keyboard *key);
};

#endif // BUTTONS_MANAGER
