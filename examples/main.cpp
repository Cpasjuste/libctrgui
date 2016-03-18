#include <3ds.h>
#include "../source/gui.hpp"

Gui *gui;

int main(int argc, char *argv[]) {

    gui = new Gui();

    // add a font and a text msg
    Font *fnt = new Font("font.ttf", "fnt1");
    Text *txt = new Text("topInfo", "hello", 16, RGBA8(0, 0, 0, 255));
    fnt->add(txt);
    gui->topScreen->add(fnt);

    // add a rectangle to top screen
    Rectangle *r1 = new Rectangle(RGBA8(0, 0, 0, 255), "rec1", 64, 64, 64, 64);
    gui->topScreen->add(r1);

    // add a rectangle relative to rectangle 1 (r1)
    Rectangle *r2 = new Rectangle(RGBA8(255, 255, 255, 255), "rec2", 16, 16, 32, 32);
    r1->add(r2);

    // add a scaled texture
    Texture *tex1 = new Texture("test.png", "tex1", 200, 64, 64, 64);
    gui->topScreen->add(tex1);

    // add a (non scaled) texture below tex1
    Texture *tex2 = new Texture("test.png", "tex2", tex1->x, tex1->y + (int)(tex1->height*tex1->scale.y));
    gui->topScreen->add(tex2);

    while (aptMainLoop()) {

        gui->update();

        // move text
        if(gui->keyHeld & KEY_LEFT) {
            txt->x--;
        } else if(gui->keyHeld & KEY_RIGHT) {
            txt->x++;
        }

        // quit
        if(gui->keyDown & KEY_START) {
            break;
        }
    }

    // free/delete including childs
    delete gui;

    return 0;
}
