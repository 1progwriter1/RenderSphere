#ifndef BUTTONS_MANAGER
#define BUTTONS_MANAGER

#include "abutton.hpp"
#include <vector>

class ButtonsManager
{
    std::vector<AButton *> buttons_;

public:
    ButtonsManager()  = default;
    ~ButtonsManager();

    void addButton( AButton *new_button);
};

#endif // BUTTONS_MANAGER
