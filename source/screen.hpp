#ifndef SCREEN_H
#define SCREEN_H

#include <3ds.h>
#include <string>
#include <stdio.h>
#include <vector>

#include "widget.hpp"
#include "texture.hpp"

class Screen : public Widget {
public:

    Screen(gfxScreen_t screen, const std::string &name, int x, int y, int w, int h);

    gfxScreen_t screen;

    void update();

private:
};

#endif
