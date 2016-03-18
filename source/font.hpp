#ifndef FONT_H
#define FONT_H

#include <3ds.h>
#include <string>
#include <stdio.h>
#include <vector>

#include <sf2d.h>
#include <sftd.h>
#include "widget.hpp"

class Font : public Widget {
public:
    Font(const std::string &path, const std::string &name);

    ~Font();

    Widget *add(Widget *widget);

    sftd_font *font;

private:
};

#endif
