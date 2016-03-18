#ifndef TEXT_H
#define TEXT_H

#include <3ds.h>
#include <string>
#include <stdio.h>
#include <vector>

#include <sf2d.h>
#include <sftd.h>

#include "widget.hpp"
#include "font.hpp"

class Text : public Widget {
public:
    Text(const std::string &name, const std::string &text, int size = 16,
         unsigned int color = RGBA8(255, 255, 255, 255),
         int x = 0, int y = 0, int w = 0, int h = 0, bool centered = false,
         std::function<void(Widget *widget)> onTouch = NULL);

    ~Text();

    std::string text;
    unsigned int color;
    int size = 20;
    Font *font;

private:
    void draw(int x, int y, int w, int h);
};

#endif
