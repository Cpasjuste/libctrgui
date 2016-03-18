#ifndef GUI_H
#define GUI_H

#include <3ds.h>
#include <string>
#include <stdio.h>

#include "widget.hpp"
#include "font.hpp"
#include "text.hpp"
#include "screen.hpp"
#include "texture.hpp"
#include "main.hpp"

class Gui {
public:

    Gui();

    ~Gui();

    void update();

    bool available = false;
    Widget *topScreen;
    Widget *bottomScreen;
    u32 keyDown;
    u32 keyHeld;

private:

};

#endif
