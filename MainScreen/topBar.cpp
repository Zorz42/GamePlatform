//
//  topBar.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 25/10/2020.
//

#include "topBar.h"

#define BUTTON_SIZE 50
#define BUTTON_SPACING 10

Swl::rect_c buttons[3], selection_rect_top;
int selected_top_bar = 0;

void topBar::init() {
    selection_rect_top.w = BUTTON_SIZE + BUTTON_SPACING;
    selection_rect_top.h = BUTTON_SIZE + BUTTON_SPACING;
    selection_rect_top.y = BUTTON_SPACING / 2;
    selection_rect_top.c = {80, 80, 80};
    selection_rect_top.corner_radius = BUTTON_SPACING;
    for(int i = 0; i < 3; i++) {
        buttons[i].w = BUTTON_SIZE;
        buttons[i].h = BUTTON_SIZE;
        buttons[i].x = BUTTON_SPACING * (i + 1) + BUTTON_SIZE * i;
        buttons[i].y = BUTTON_SPACING;
        buttons[i].c = {255, 255, 255};
        buttons[i].corner_radius = BUTTON_SPACING / 2;
    }
}

bool topBar::handleEvents(SDL_Event &event) {
    return false;
}

void topBar::render() {
    swl.draw(selection_rect_top);
    for(Swl::rect_c& i : buttons)
        swl.draw(i);
}
