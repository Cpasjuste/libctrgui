#ifndef WIDGET_H
#define WIDGET_H

#include <string>
#include <cstdio>
#include <vector>
#include <functional>
#include <sf2d.h>

class Widget {
public:
    struct Scale {
        Scale() : x(1), y(1) { };

        Scale(float x, float y) : x(x), y(y) { };
        float x = 1, y = 1;
    };

    Widget(const std::string &name, int x = 0, int y = 0, int w = 0, int h = 0, bool centered = false,
           std::function<void(Widget *widget)> onTouch = NULL);

    virtual ~Widget();

    virtual void update();

    virtual Widget *add(Widget *widget);

    void remove(Widget *widget);

    Widget *parent;
    std::string name;
    int x, y, width, height; // x/y relative to parent
    Scale scale;
    bool centered = false;

    int getAbsX(); // absolute (real) position x
    int getAbsY(); // absolute (real) position y
    bool shown = true;
    bool available = true;

protected:

private:
    std::vector<Widget *> widgets;

    void init(const std::string &name, int x, int y, int w, int h, bool centered = false,
              std::function<void(Widget *widget)> onTouch = NULL);

    virtual void draw(int x, int y, int w, int h) { };
    int absx, absy;
    std::function<void(Widget *widget)> onTouch = NULL;
};

#endif
