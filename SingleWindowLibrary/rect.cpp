//
//  draw.cpp
//  SingleWindowLibrary
//
//  Created by Jakob Zorz on 12/09/2020.
//

#include "swl.h"

void Swl::draw(rect& obj) {
    if(obj.filled)
        SDL_RenderFillRect(_renderer, (SDL_Rect*)((void*)&obj));
    else
        SDL_RenderDrawRect(_renderer, (SDL_Rect*)((void*)&obj));
}

void Swl::draw(rect_c& obj) {
    swl.pushDrawColor(obj.c);
    if(obj.filled)
        SDL_RenderFillRect(_renderer, (SDL_Rect*)((void*)&obj));
    else
        SDL_RenderDrawRect(_renderer, (SDL_Rect*)((void*)&obj));
    swl.popDrawColor();
}

void Swl::draw_rect(int x, int y, int w, int h, bool fill) {
    SDL_Rect temp_rect = {x, y, w, h};
    if(fill)
        SDL_RenderFillRect(_renderer, &temp_rect);
    else
        SDL_RenderDrawRect(_renderer, &temp_rect);
}

void Swl::draw_rect(int x, int y, int w, int h, color c, bool fill) {
    swl.pushDrawColor(c);
    SDL_Rect temp_rect = {x, y, w, h};
    if(fill)
        SDL_RenderFillRect(_renderer, &temp_rect);
    else
        SDL_RenderDrawRect(_renderer, &temp_rect);
    swl.popDrawColor();
}
