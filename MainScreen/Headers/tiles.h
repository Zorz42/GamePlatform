//
//  tiles.h
//  GamePlatform
//
//  Created by Jakob Zorz on 25/10/2020.
//

#include "swl.h"

namespace tiles {
void init();
bool handleEvents(SDL_Event& event);
void render();
inline bool on_tiles = true;
}
