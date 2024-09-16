#ifndef BUTTONS_MANAGER
#define BUTTONS_MANAGER

#include "abutton.hpp"
#include <vector>

class ButtonsManager
{
    std::vector<AButton> buttons;
public:
    ButtonsManager()  = default;
    ~ButtonsManager() = default;
};

#endif // BUTTONS_MANAGER
