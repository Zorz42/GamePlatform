//
//  tiles.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 25/10/2020.
//

#include "tiles.h"
#include "joystickDriver.h"
#include <vector>

#define TILE_SIZE 500
#define TILE_SPACING 100
#define DIVIDER 7
#define INITIAL_VELOCITY 1000
#define PEAK_VELOCITY 320
#define ACCELERATION 30

struct tile {
public:
    Swl::color color;
    std::string text;
    void render(unsigned int index, bool on_tiles);
    void renderText();
    tile(Swl::color color, std::string text) : color(color), text(text) {}
private:
    Swl::texture _text_texture;
};

namespace tiles {
void init();
}

std::vector<tile> tiles_arr;
int axis_position = 0, to_go = 0, position = 0, selected = 0;
Swl::rect_c selection_rect;

void tile::render(unsigned int index, bool on_tiles) {
    Swl::rect_c draw_rect;
    draw_rect.w = TILE_SIZE;
    draw_rect.h = TILE_SIZE;
    draw_rect.x = swl.window_width / 2 - draw_rect.w / 2 + index * (draw_rect.w + TILE_SPACING) - position;
    draw_rect.y = swl.window_height / 2 - draw_rect.h / 2;
    draw_rect.c = color;
    draw_rect.corner_radius = TILE_SPACING / 2;
    swl.draw(draw_rect);
    if(on_tiles && index == selected)
        swl.draw(_text_texture);
}

void tile::renderText() {
    _text_texture.loadFromText(text, {255, 255, 255});
    _text_texture.x = swl.window_width / 2 - _text_texture.getWidth() / 2;
    _text_texture.y = swl.window_height / 2 + TILE_SIZE / 2 + TILE_SPACING / 4 * 3;
}

void tiles::init() {
    tiles_arr = {
        tile({255, 0 ,0}, "turn off"),
        tile({0, 255, 0}, "tile1"),
        tile({255, 255, 0}, "tile2"),
        tile({0, 0, 255}, "tile3"),
        tile({255, 0, 255}, "tile4"),
        tile({0, 255, 255}, "tile5"),
        tile({255, 255, 255}, "tile6"),
    };
    for(tile& iter : tiles_arr)
        iter.renderText();
    
    selection_rect.w = TILE_SIZE + TILE_SPACING;
    selection_rect.h = TILE_SIZE + TILE_SPACING;
    selection_rect.y = swl.window_height / 2 - selection_rect.h / 2;
    selection_rect.c = {80, 80, 80};
    selection_rect.corner_radius = TILE_SPACING;
}

bool tiles::handleEvents(SDL_Event &event) {
    if(on_tiles && event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == jd::button::cross && !selected)
        swl.stop();
    return false;
}

void tiles::render() {
    static bool prev_active = false, prev_still = true, waiting_axis = false;
    static int velocity = INITIAL_VELOCITY;
    if(on_tiles) {
        if(!prev_active)
            waiting_axis = true;
        prev_active = true;
        if(!jd::left_axis_x) {
            axis_position = to_go;
            prev_still = true;
            velocity = INITIAL_VELOCITY;
            waiting_axis = false;
        }
        else if(!waiting_axis && abs(jd::left_axis_x) > abs(jd::left_axis_y * 3)) {
            axis_position += prev_still && jd::left_axis_x > 0 ? TILE_SIZE + TILE_SPACING : jd::left_axis_x / velocity;
            prev_still = false;
            if(velocity >= PEAK_VELOCITY)
                velocity -= ACCELERATION;
        }
        if(axis_position < 0)
            axis_position = 0;
        else if(axis_position > (TILE_SIZE + TILE_SPACING) * (tiles_arr.size() - 1))
            axis_position = (TILE_SIZE + TILE_SPACING) * (unsigned int)(tiles_arr.size() - 1);
    }
    else
        prev_active = false;
    
    selected = axis_position / (TILE_SIZE + TILE_SPACING);
    to_go = selected * (TILE_SIZE + TILE_SPACING);
    position = abs(position - to_go) < DIVIDER ? to_go : position + (to_go - position) / DIVIDER;
    
    if(on_tiles) {
        selection_rect.x = swl.window_width / 2 - selection_rect.w / 2 + to_go - position;
        swl.draw(selection_rect);
        
        if(!waiting_axis && jd::left_axis_y < -30000)
            on_tiles = false;
    }
    for(unsigned int i = 0; i < tiles_arr.size(); i++)
        tiles_arr.at(i).render(i, on_tiles);
}
