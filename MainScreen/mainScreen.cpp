#include "swl.h"
#include "mainScreen.h"
#include "joystickDriver.h"
#include "tiles.h"
#include "topBar.h"
#include "selectionRect.h"
#include <ctime>
#include <iomanip>
#include <sstream>

#define TIME_SPACING_RIGHT 25

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
    
    static Swl::texture time_texture;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream time_string;
    time_string << std::put_time(&tm, "%H:%M");
    time_texture.loadFromText(time_string.str(), {255, 255, 255});
    time_texture.x = swl.window_width - time_texture.getWidth() - TIME_SPACING_RIGHT;
    swl.draw(time_texture);
}
