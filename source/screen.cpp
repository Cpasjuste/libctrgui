#include <3ds.h>
#include <string>
#include <sf2d.h>
#include "screen.hpp"

Screen::Screen(gfxScreen_t screen,
               const std::string &name, int x, int y, int w, int h)
        : Widget(name, x, y, w, h) {
    this->screen = screen;
}

void Screen::update() {
    sf2d_start_frame(this->screen, GFX_LEFT);
    Widget::update();
    sf2d_end_frame();
}
