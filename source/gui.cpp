#include <string>
#include <sf2d.h>

#include "gui.hpp"
#include "utility.hpp"


Gui::Gui() {
    sf2d_init();
    sf2d_set_clear_color(RGBA8(0xe2, 0xe2, 0xea, 0xFF));
    sf2d_set_vblank_wait(1);

    sftd_init();

    this->topScreen = new Screen(GFX_TOP, "ScreenTop", 0, 0, 400, 240);
    this->bottomScreen = new Screen(GFX_BOTTOM, "ScreenBottom", 0, 0, 320, 240);
    this->available = true;

    Utility::openSD();
}

void Gui::update() {
    if (!this->available)
        return;

    hidScanInput();
    keyDown = hidKeysDown();
    keyHeld = hidKeysHeld();

    this->topScreen->update();
    this->bottomScreen->update();

    sf2d_swapbuffers();
}

Gui::~Gui() {
    if (!this->available)
        return;

    delete this->topScreen;
    delete this->bottomScreen;
    sftd_fini();
    sf2d_fini();

    Utility::closeSD();
}
