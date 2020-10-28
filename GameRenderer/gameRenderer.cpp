//
//  gameRenderer.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 28/10/2020.
//

#include "swl.h"
#include "gameRenderer.h"
#include "joystickDriver.h"
#include "mainScreen.h"

void game_event(SDL_Event& event);
void game_main();
Swl::scene game_scene(&game_main, &game_event);
gameReader::game* curr_game = nullptr;

void gameRenderer::launchGame(gameReader::game& game) {
    curr_game = &game;
    swl.switchScene(game_scene);
}

void game_event(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        swl.stop();
    else if(jd::handleEvents(event));
    else if(event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == jd::button::cross)
        swl.switchScene(mainScreen::main_screen_scene);
}


void game_main() {
    
}
