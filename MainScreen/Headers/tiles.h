//
//  tiles.h
//  GamePlatform
//
//  Created by Jakob Zorz on 25/10/2020.
//

#include "swl.h"

#define TILE_SIZE 512
#define TILE_SPACING 128
#define DIVIDER 7
#define INITIAL_VELOCITY 1000
#define PEAK_VELOCITY 320
#define ACCELERATION 30

namespace tiles {
void init();
bool handleEvents(SDL_Event& event);
void render();
}
