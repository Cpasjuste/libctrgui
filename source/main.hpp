#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <3ds.h>
#include <string>
#include <stdio.h>
#include <vector>

#include <sf2d.h>
#include "widget.hpp"

class Rectangle : public Widget {
public:
    Rectangle(u32 color, const std::string &name, int x, int y, int w, int h, bool centered = false,
              std::function<void(Widget *widget)> onTouch = NULL);

private:
    u32 color;

    void draw(int x, int y, int w, int h);
};

#endif
