#include "swl.h"
#include "joystickDriver.h"
#include "tiles.h"
#include "topBar.h"

void main();
void main_event(SDL_Event& event);
Swl::scene main_scene(&main, &main_event);

int init_start;

void preInit() {
    init_start = SDL_GetTicks();
    swl.load_font = true;
    swl.font_path = "../Resources/arial.ttf";
    swl.font_size = 32;
    
    swl.goFullscreen();
    SDL_ShowCursor(SDL_DISABLE);
    swl.enableVsync();
}

void postInit() {
    jd::init();
    main_scene.background_color = {10, 10, 10};
    swl.switchScene(main_scene);
    tiles::init();
    topBar::init();
    std::cout << "Init done in: " << (float)(SDL_GetTicks() - init_start) / 1000 << "s" << std::endl;
}

void main_event(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        swl.stop();
    else if(jd::handleEvents(event));
    else if(tiles::handleEvents(event));
    else
        topBar::handleEvents(event);
}

void main() {
    tiles::render();
    topBar::render();
}
