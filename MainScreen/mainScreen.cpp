#include "swl.h"
#include "mainScreen.h"
#include "joystickDriver.h"
#include "tiles.h"
#include "topBar.h"
#include "selectionRect.h"

void mainScreen::init() {
    main_screen_scene.background_color = {10, 10, 10};
    tiles::init();
    topBar::init();
    selectionRect::init();
}

void mainScreen::main_event(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        swl.stop();
    else if(jd::handleEvents(event));
    else if(tiles::handleEvents(event));
    else
        topBar::handleEvents(event);
}

void mainScreen::main_render() {
    selectionRect::render();
    tiles::render();
    topBar::render();
}
