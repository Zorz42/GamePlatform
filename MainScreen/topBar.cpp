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

#define VELOCITY 5000
#define DIVIDER 3

int button_size = 50, button_spacing = 10, initial_button_spacing = 40, button_size_to_go = button_size, button_spacing_to_go = button_spacing, initial_button_spacing_to_go = initial_button_spacing;
int selected_top_bar = 0, axis_position_top_bar = 0, position_top_bar = 0;

void topBar::init() {
    
}

bool topBar::handleEvents(SDL_Event &event) {
    return false;
}

void topBar::render() {
    button_size = abs(button_size - button_size_to_go) < DIVIDER ? button_size_to_go : button_size + (button_size_to_go - button_size) / DIVIDER;
    button_spacing = abs(button_spacing - button_spacing_to_go) < DIVIDER ? button_spacing_to_go : button_spacing + (button_spacing_to_go - button_spacing) / DIVIDER;
    initial_button_spacing = abs(initial_button_spacing - initial_button_spacing_to_go) < DIVIDER ? initial_button_spacing_to_go : initial_button_spacing + (initial_button_spacing_to_go - initial_button_spacing) / DIVIDER;
    
    static bool prev_active = false, prev_still = true, waiting_axis = false;
    if(!mainScreen::on_tiles) {
        button_size_to_go = 70;
        button_spacing_to_go = 15;
        initial_button_spacing_to_go = 80;
        
        if(!prev_active) {
            selectionRect::w = button_size_to_go + button_spacing_to_go;
            selectionRect::h = button_size_to_go + button_spacing_to_go;
            selectionRect::x = button_spacing_to_go / 2;
            selectionRect::y = button_spacing_to_go / 2;
            selectionRect::corner_radius = button_spacing_to_go;
            waiting_axis = true;
        }
        prev_active = true;
        if(!jd::left_axis_x) {
            axis_position_top_bar = position_top_bar;
            prev_still = true;
            waiting_axis = false;
        }
        else if(!waiting_axis && abs(jd::left_axis_x) > abs(jd::left_axis_y)) {
            axis_position_top_bar += prev_still && jd::left_axis_x > 0 ? button_size + button_spacing : jd::left_axis_x / VELOCITY;
            prev_still = false;
        }
        if(axis_position_top_bar < 0)
            axis_position_top_bar = 0;
        else if(axis_position_top_bar > (button_size + button_spacing) * 2)
            axis_position_top_bar = (button_size + button_spacing) * 2;
        
        selected_top_bar = axis_position_top_bar / (button_size + button_spacing);
        position_top_bar = selected_top_bar * (button_size + button_spacing);
        
        selectionRect::x = selected_top_bar * (button_size + button_spacing) + initial_button_spacing - button_spacing / 2;
        
        if(!waiting_axis && jd::left_axis_y > 30000)
            mainScreen::on_tiles = true;
    }
    else {
        prev_active = false;
        button_size_to_go = 50;
        button_spacing_to_go = 10;
        initial_button_spacing_to_go = 10;
    }
    
    for(int i = 0; i < 3; i++) {
        Swl::rect_c button;
        button.w = button_size;
        button.h = button_size;
        button.x = i * (button_size + button_spacing) + initial_button_spacing;
        button.y = button_spacing;
        button.c = {255, 255, 255};
        button.corner_radius = button_spacing / 2;
        swl.draw(button);
    }
}
