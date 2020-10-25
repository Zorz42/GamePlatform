//
//  mainScreen.h
//  GamePlatform
//
//  Created by Jakob Zorz on 25/10/2020.
//

#include "swl.h"

namespace mainScreen {
inline bool on_tiles = true;
void init();
void main_render();
void main_event(SDL_Event& event);
inline Swl::scene main_screen_scene(&main_render, &main_event);
}
