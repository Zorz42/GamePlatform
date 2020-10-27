//
//  main.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 25/10/2020.
//

#include "swl.h"
#include "mainScreen.h"
#include "joystickDriver.h"
#include "fileSystem.h"

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
    fileSystem::init();
    mainScreen::init();
    swl.switchScene(mainScreen::main_screen_scene);
    std::cout << "Init done in: " << (float)(SDL_GetTicks() - init_start) / 1000 << "s" << std::endl;
}
