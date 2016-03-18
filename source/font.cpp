#include <string>
#include <stdio.h>

#include "font.hpp"
#include "text.hpp"
#include "utility.hpp"

Font::Font(const std::string &path, const std::string &name)
        : Widget(name, 0, 0, 0, 0, false, NULL) {
    Utility::debug("%s: Font", name.c_str());

    if (!Utility::fileExist(path)) {
        Utility::debug("Err: file doesn't exist: %s", path.c_str());
        this->available = false;
        return;
    }

    this->font = sftd_load_font_file(path.c_str());
    if (this->font == NULL) {
        Utility::debug("Err: sftd_load_font: %s", path.c_str());
        this->available = false;
        return;
    }

    Utility::debug("Loaded: %s (%ix%i)\n", path.c_str());
}

Widget *Font::add(Widget *widget) {
/*
    widget->parent = this;
    widget->absx = this->absx + widget->x;
    widget->absy = this->absy + widget->y;
    widgets.push_back(widget);
    Utility::debug("%s: childs=%i", name.c_str(), widgets.size());
    return widget;
*/
    Utility::debug("%s", name.c_str());
    Text *text = (Text *) widget;
    text->font = this;
    if (!available)
        text->available = false;

    return Widget::add(widget);
}

Font::~Font() {
    Utility::debug("%s: ~Font", name.c_str());
    if (this->available
        && this->font != NULL) {
        sftd_free_font(this->font);
        this->font = NULL;
    }
}
