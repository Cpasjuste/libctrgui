#include <string>
#include <vector>

#include "text.hpp"
#include "utility.hpp"

Text::Text(const std::string &name, const std::string &text,
           int size, unsigned int color, int x, int y, int w, int h,
           bool centered, std::function<void(Widget *widget)> onTouch)
        : Widget(name, x, y, w, h, centered, onTouch) {
    Utility::debug("%s: Text", name.c_str());

    this->text = text;
    this->size = size;
    this->color = color;
}

void Text::draw(int x, int y, int w, int h) {
    if (this->available) {
        if (text.find("\n") != std::string::npos) {
            sftd_calc_bounding_box(&this->width, &this->height, font->font, size, 400, "bpAj");
            std::vector<std::string> tokens = Utility::split(text, '\n');
            for (int i = 0; i < tokens.size(); i++) {
                sftd_draw_text(this->font->font, x, y + this->height * i, color, size, tokens[i].c_str());
            }
        }
        else {
            sftd_draw_text(this->font->font, x, y, color, size, text.c_str());
        }
    }
}

Text::~Text() {
    Utility::debug("%s: ~Text", name.c_str());
}

