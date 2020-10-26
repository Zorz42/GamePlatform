//
//  selectionRect.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 26/10/2020.
//

#include "selectionRect.h"
#include "swl.h"

#define DIVIDER 3

Swl::rect_c selection_rect, selection_rect_outline;

void selectionRect::init() {
    selection_rect.c = {80, 80, 80};
    selection_rect_outline.c = {255, 255, 255};
}

void selectionRect::render() {
    selection_rect.x = abs(selection_rect.x - selectionRect::x) < DIVIDER ? selectionRect::x : selection_rect.x + (selectionRect::x - selection_rect.x) / DIVIDER;
    selection_rect.y = abs(selection_rect.y - selectionRect::y) < DIVIDER ? selectionRect::y : selection_rect.y + (selectionRect::y - selection_rect.y) / DIVIDER;
    selection_rect.w = abs(selection_rect.w - selectionRect::w) < DIVIDER ? selectionRect::w : selection_rect.w + (selectionRect::w - selection_rect.w) / DIVIDER;
    selection_rect.h = abs(selection_rect.h - selectionRect::h) < DIVIDER ? selectionRect::h : selection_rect.h + (selectionRect::h - selection_rect.h) / DIVIDER;
    selection_rect.corner_radius = abs(selection_rect.corner_radius - selectionRect::corner_radius) < DIVIDER ? selectionRect::corner_radius : selection_rect.corner_radius + (selectionRect::corner_radius - selection_rect.corner_radius) / DIVIDER;
    
    selection_rect_outline.x = selection_rect.x - 1;
    selection_rect_outline.y = selection_rect.y - 1;
    selection_rect_outline.w = selection_rect.w + 2;
    selection_rect_outline.h = selection_rect.h + 2;
    selection_rect_outline.corner_radius = selection_rect.corner_radius;
    
    swl.draw(selection_rect_outline);
    swl.draw(selection_rect);
}

void selectionRect::teleport() {
    selection_rect.x = selectionRect::x;
    selection_rect.y = selectionRect::y;
    selection_rect.w = selectionRect::w;
    selection_rect.h = selectionRect::h;
    selection_rect.corner_radius = selectionRect::corner_radius;
}
