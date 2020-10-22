#include "swl.h"

void main();
void main_event(SDL_Event& event);
Swl::scene main_scene(&main, &main_event);

Swl::texture text;
Swl::rect_c test_rect;

void preInit() {
    //swl.window_width = 640;
    //swl.window_height = 400;
    //swl.window_caption = "Untitled";
    //swl.load_font = false;
    //swl.font_size = 32;
    
    // this library already comes with arial.ttf
    //swl.font_path = "/path/to/font.ttf";
    swl.goFullscreen();
}

void postInit() {
    swl.switchScene(main_scene);
    std::cout << swl.window_width << std::endl;
    test_rect.w = 100;
    test_rect.h = 100;
    test_rect.x = swl.window_width - test_rect.w;
    test_rect.y = swl.window_height - test_rect.h;
    test_rect.c = {255, 255, 255};
}

void main_event(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        swl.stop();
}

void main() {
    swl.draw(test_rect);
    if(SDL_NumJoysticks() == 0)
        swl.switchScene(no_controller_scene);
}

void controller_main() {
    swl.draw(background_rect);
    if(SDL_NumJoysticks() != 0)
        swl.switchScene(main_scene);
    /* this is the main loop which executes every frame */
}
