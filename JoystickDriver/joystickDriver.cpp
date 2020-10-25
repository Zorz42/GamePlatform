//
//  core.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 23/10/2020.
//

#include <iostream>
#include "swl.h"
#include "joystickDriver.h"

SDL_Joystick* main_joystick = nullptr;

void no_controller_main();
Swl::scene no_controller_scene(&no_controller_main);
Swl::scene* prev_scene = nullptr;
Swl::texture no_controller_texture;

#define AXIS_DEAD_ZONE 10000

void jd::init() {
    if(SDL_NumJoysticks()) {
        main_joystick = SDL_JoystickOpen(0);
        SDL_JoystickSetPlayerIndex(main_joystick, 1);
    }
    else
        no_controller_at_start = true;
    no_controller_texture.loadFromText("No controller connected!", {255, 255, 255});
}

void switch_to_controller_scene() {
    prev_scene = &swl.getCurrScene();
    swl.switchScene(no_controller_scene);
}

bool jd::handleEvents(SDL_Event& event) {
    if(no_controller_at_start) {
        no_controller_at_start = false;
        switch_to_controller_scene();
    }
    if(event.type == SDL_JOYAXISMOTION) {
        switch(event.jaxis.axis) {
            case SDL_CONTROLLER_AXIS_LEFTX:
                left_axis_x = event.jaxis.value;
                if(abs(left_axis_x) < AXIS_DEAD_ZONE && abs(left_axis_y) < AXIS_DEAD_ZONE)
                    left_axis_x = 0;
                break;
            case SDL_CONTROLLER_AXIS_LEFTY:
                left_axis_y = event.jaxis.value;
                if(abs(left_axis_x) < AXIS_DEAD_ZONE && abs(left_axis_y) < AXIS_DEAD_ZONE)
                    left_axis_y = 0;
                break;
            case SDL_CONTROLLER_AXIS_RIGHTX:
                right_axis_x = event.jaxis.value;
                if(abs(right_axis_x) < AXIS_DEAD_ZONE && abs(right_axis_y) < AXIS_DEAD_ZONE)
                    right_axis_x = 0;
                break;
            case SDL_CONTROLLER_AXIS_RIGHTY:
                right_axis_y = event.jaxis.value;
                if(abs(right_axis_x) < AXIS_DEAD_ZONE && abs(right_axis_y) < AXIS_DEAD_ZONE)
                    right_axis_y = 0;
                break;
        }
        return true;
    }
    else if(event.type == SDL_JOYDEVICEREMOVED && !SDL_NumJoysticks())
        switch_to_controller_scene();
    return false;
}

void no_controller_event(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        swl.stop();
}

void no_controller_main() {
    if(SDL_NumJoysticks()) {
        main_joystick = SDL_JoystickOpen(0);
        SDL_JoystickSetPlayerIndex(main_joystick, 1);
        swl.switchScene(*prev_scene);
    }
    swl.draw(no_controller_texture);
}
