#include <3ds.h>
#include <string>

#include "main.hpp"

Rectangle::Rectangle(u32 color, const std::string &name, int x, int y, int w, int h, bool centered,
                     std::function<void(Widget *widget)> onTouch)
        : Widget(name, x, y, w, h, centered, onTouch) {
    this->color = color;
}

void Rectangle::draw(int x, int y, int w, int h) {
    sf2d_draw_rectangle(x, y, w, h, color);
}
