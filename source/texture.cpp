#include <3ds.h>
#include <string>
#include <stdio.h>

#include "texture.hpp"
#include "utility.hpp"

static inline bool endsWith(std::string const &value, std::string const &ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

Texture::Texture(const std::string &path,
                 const std::string &name, int x, int y, int w, int h, bool centered,
                 std::function<void(Widget *widget)> onTouch)
        : Widget(name, x, y, w, h, centered, onTouch) {
    //Utility::debug("%s: Texture\n", name.c_str());

    if (!Utility::fileExist(path)) {
        Utility::debug("Err: file doesn't exist: %s\n", path.c_str());
        this->available = false;
        return;
    }

    if (endsWith(path, ".png")) {
        this->texData = sfil_load_PNG_file(path.c_str(), SF2D_PLACE_RAM);
    } else if (endsWith(path, ".bmp")) {
        Utility::debug("sfil_load_BMP_file:%s\n", path.c_str());
        this->texData = sfil_load_BMP_file(path.c_str(), SF2D_PLACE_RAM);
        Utility::debug("sfil_load_BMP_file: done\n", path.c_str());
    }

    if (this->texData == NULL) {
        Utility::debug("Err: sfil_load_file: %s\n", path.c_str());
        this->available = false;
        return;
    }

    this->width = this->texData->width;
    this->height = this->texData->height;

    if(w > 0 && h > 0) {
        if (this->width != w || this->height != h)
            this->scale = Scale((float) w / this->width, (float) h / this->height);
    }

    Utility::debug("Loaded: %s (%ix%i)\n", path.c_str(), w, h);
}

Texture::Texture(u8 *pixels,
                 const std::string &name, int x, int y, int w, int h, bool centered,
                 std::function<void(Widget *widget)> onTouch)
        : Widget(name, x, y, w, h, centered, onTouch) {
    //Utility::debug("%s: Texture\n", name.c_str());

    if (pixels == NULL) {
        Utility::debug("Err: pixels == NULL\n");
        this->available = false;
        return;
    }

    this->texData =
            sf2d_create_texture_mem_RGBA8(pixels, w, h, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    if (this->texData == NULL) {
        Utility::debug("Err: sf2d_create_texture_mem_RGBA8\n");
        this->available = false;
        return;
    }

    this->width = this->texData->width;
    this->height = this->texData->height;
    // handle scaling
    if (this->width != w || this->height != h)
        this->scale = Scale((float) w / this->width, (float) h / this->height);

    Utility::debug("Loaded: %s (%ix%i)\n", name.c_str(), w, h);
}

void Texture::draw(int x, int y, int w, int h) {
    if (this->available) {
        sf2d_draw_texture_scale(this->texData, x, y, this->scale.x, this->scale.y);
    }
}

Texture::~Texture() {
    //Utility::debug("%s: ~Texture\n", name.c_str());
    if (this->available
        && this->texData != NULL) {
        sf2d_free_texture(this->texData);
        this->texData = NULL;
    }
}
