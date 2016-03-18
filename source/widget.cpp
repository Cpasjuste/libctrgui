#include <string>
#include <cstdio>
#include <algorithm>

#include "widget.hpp"
#include "utility.hpp"

Widget::Widget(
        const std::string &name, int x, int y, int w, int h, bool centered,
        std::function<void(Widget *widget)> onTouch) {
    init(name, x, y, w, h, centered, onTouch);
}

void Widget::init(const std::string &name, int x, int y, int w, int h, bool centered,
                  std::function<void(Widget *widget)> onTouch) {
    this->name = name;
    this->parent = NULL;
    this->centered = centered;
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    this->onTouch = onTouch;
}

Widget *Widget::add(Widget *widget) {
    widget->parent = this;
    widgets.push_back(widget);
    return widget;
}

/*
Widget *Widget::find(const std::string &_name) {
    std::find_if(widgets.begin(), widgets.end(), [&_name](Widget *w)
        { return w->name == _name; });
}
*/

void Widget::remove(Widget *widget) {
    if (widget != NULL) {
        widgets.erase(std::remove(widgets.begin(), widgets.end(), widget), widgets.end());
        delete widget;
        widget = NULL;
    }
}

void Widget::update() {
    if (!this->shown)
        return;

    int _x = centered ? x - width / 2 : x;
    int _y = centered ? y - height / 2 : y;
    int _w = width * scale.x;
    int _h = height * scale.y;
    if (centered && (scale.x != 1 || scale.y != 1)) {
        _x += (width - _w) / 2;
        _y += (height - _h) / 2;
    }
    if (parent != NULL) {
        absx = x + parent->x;
        absy = y + parent->y;
        _x += parent->centered ? parent->absx - parent->width / 2 : parent->absx;
        _y += parent->centered ? parent->absy - parent->height / 2 : parent->absy;
    }
    if (onTouch != NULL && (hidKeysDown() & KEY_TOUCH)) {
        touchPosition touch;
        hidTouchRead(&touch);
        if (touch.px >= _x && touch.px <= _x + _w
            && touch.py >= _y && touch.py <= _y + _w) {
            onTouch(this);
        }
    }
    draw(_x, _y, _w, _h);

    // update child widgets, remove if necessary (deleted)
    std::vector<Widget *>::iterator widget = widgets.begin();
    while (widget != widgets.end()) {
        //Utility::debug("%s-> %p (%i)", (*widget)->name.c_str(), *widget, (*widget)->widgets.size());
        if ((*widget) == NULL) {
            Utility::debug("deleting obselete widget...\n");
            widget = widgets.erase(widget);
        }
        else {
            (*widget)->update();
            ++widget;
        }
    }
}

Widget::~Widget() {
    //Utility::debug("%s: ~Widget.start", name.c_str());
    for (std::vector<Widget *>::iterator widget = widgets.begin(); widget != widgets.end(); ++widget) {
        if (*widget) {
            delete *widget;
            *widget = NULL;
        }
    }
    widgets.clear();
    //Utility::debug("%s: ~Widget.end", name.c_str());
}
