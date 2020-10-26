//
//  topBar.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 25/10/2020.
//

#include "topBar.h"
#include "joystickDriver.h"
#include "mainScreen.h"
#include "selectionRect.h"

#define BUTTON_SIZE 50
#define BUTTON_SPACING 10
#define INITIAL_BUTTON_SPACING (BUTTON_SPACING * 4)
#define VELOCITY 5000

Swl::rect_c buttons[3];
int selected_top_bar = 0, axis_position_top_bar = 0, position_top_bar = 0;

void topBar::init() {
    for(int i = 0; i < 3; i++) {
        buttons[i].w = BUTTON_SIZE;
        buttons[i].h = BUTTON_SIZE;
        buttons[i].x = i * (BUTTON_SIZE + BUTTON_SPACING) + INITIAL_BUTTON_SPACING;
        buttons[i].y = BUTTON_SPACING;
        buttons[i].c = {255, 255, 255};
        buttons[i].corner_radius = BUTTON_SPACING / 2;
    }
}

bool topBar::handleEvents(SDL_Event &event) {
    return false;
}

void topBar::render() {
    static bool prev_active = false, prev_still = true, waiting_axis = false;
    if(!mainScreen::on_tiles) {
        if(!prev_active) {
            selectionRect::w = BUTTON_SIZE + BUTTON_SPACING;
            selectionRect::h = BUTTON_SIZE + BUTTON_SPACING;
            selectionRect::x = BUTTON_SPACING / 2;
            selectionRect::y = BUTTON_SPACING / 2;
            selectionRect::corner_radius = BUTTON_SPACING;
            waiting_axis = true;
        }
        prev_active = true;
        if(!jd::left_axis_x) {
            axis_position_top_bar = position_top_bar;
            prev_still = true;
            waiting_axis = false;
        }
        else if(!waiting_axis && abs(jd::left_axis_x) > abs(jd::left_axis_y)) {
            axis_position_top_bar += prev_still && jd::left_axis_x > 0 ? BUTTON_SIZE + BUTTON_SPACING : jd::left_axis_x / VELOCITY;
            prev_still = false;
        }
        if(axis_position_top_bar < 0)
            axis_position_top_bar = 0;
        else if(axis_position_top_bar > (BUTTON_SIZE + BUTTON_SPACING) * 2)
            axis_position_top_bar = (BUTTON_SIZE + BUTTON_SPACING) * 2;
        
        selected_top_bar = axis_position_top_bar / (BUTTON_SIZE + BUTTON_SPACING);
        position_top_bar = selected_top_bar * (BUTTON_SIZE + BUTTON_SPACING);
        
        selectionRect::x = selected_top_bar * (BUTTON_SIZE + BUTTON_SPACING) + INITIAL_BUTTON_SPACING - BUTTON_SPACING / 2;
        
        if(!waiting_axis && jd::left_axis_y > 30000)
            mainScreen::on_tiles = true;
    }
    else
        prev_active = false;
    
    for(Swl::rect_c& i : buttons)
        swl.draw(i);
}
