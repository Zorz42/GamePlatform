#include "swl.h"

void main();
void main_event(SDL_Event& event);
Swl::scene main_scene(&main, &main_event);

void controller_main();
Swl::scene no_controller_scene(&controller_main);

Swl::rect_c test_rect;
Swl::rect_c background_rect;

SDL_Joystick* main_joystick;

void preInit() {
    //swl.window_width = 640;
    //swl.window_height = 400;
    //swl.window_caption = "Untitled";
    //swl.load_font = false;
    //swl.font_size = 32;
    
    // this library already comes with arial.ttf
    //swl.font_path = "/path/to/font.ttf";
    //swl.goFullscreen();
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    main_joystick = SDL_JoystickOpen(0);
}

void postInit() {
    swl.switchScene(main_scene);
    test_rect.w = 100;
    test_rect.h = 100;
    test_rect.x = swl.window_width - test_rect.w;
    test_rect.y = swl.window_height - test_rect.h;
    test_rect.c = {255, 255, 255};
    
    background_rect.w = swl.window_width;
    background_rect.h = swl.window_height;
    background_rect.c = {100, 100, 100};
}

void main_event(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        swl.stop();
    else if(event.type == SDL_JOYAXISMOTION) {
        //std::cout << event.jaxis.value << std::endl;
    }
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
}
