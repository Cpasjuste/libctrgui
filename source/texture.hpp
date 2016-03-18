#ifndef TEXTURE_H
#define TEXTURE_H

#include <3ds.h>
#include <string>
#include <stdio.h>
#include <vector>

#include <sf2d.h>
#include <sfil.h>
#include "widget.hpp"

class Texture : public Widget {
public:
    Texture(const std::string &path, const std::string &name, int x, int y, int w = 0, int h = 0, bool centered = false,
            std::function<void(Widget *widget)> onTouch = NULL);

    Texture(u8 *pixels, const std::string &name, int x, int y, int w, int h, bool centered = false,
            std::function<void(Widget *widget)> onTouch = NULL);

    ~Texture();

    sf2d_texture *texData;

private:
    void draw(int x, int y, int w, int h);
};

#endif
