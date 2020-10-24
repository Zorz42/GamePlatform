#include <vector>
#include "swl.h"
#include "joystickDriver.h"

#define TILE_SIZE 500
#define TILE_SPACING 100
#define DIVIDER 5
#define AXIS_SENSITIVITY 640 // lower it is, more it is sensitive

void main();
void main_event(SDL_Event& event);
Swl::scene main_scene(&main, &main_event);
int axis_position = 0, to_go = 0, position = 0, selected = 0;
Swl::rect_c selection_rect;

Swl::texture test_texture;

struct tile {
public:
    Swl::color color;
    std::string text;
    void render(unsigned int index);
    void renderText();
    tile(Swl::color color, std::string text) : color(color), text(text) {}
private:
    Swl::texture _text_texture;
};
    
void tile::render(unsigned int index) {
    Swl::rect draw_rect;
    draw_rect.w = TILE_SIZE;
    draw_rect.h = TILE_SIZE;
    draw_rect.x = swl.window_width / 2 - draw_rect.w / 2 + index * (draw_rect.w + TILE_SPACING) - position;
    draw_rect.y = swl.window_height / 2 - draw_rect.h / 2;
    swl.setDrawColor(color);
    swl.draw(draw_rect);
    if(index == selected)
        swl.draw(_text_texture);
}

void tile::renderText() {
    _text_texture.loadFromText(text, {255, 255, 255});
    _text_texture.x = swl.window_width / 2 - _text_texture.getWidth() / 2;
    _text_texture.y = swl.window_height / 2 + TILE_SIZE / 2 + TILE_SPACING / 4 * 3;
}

std::vector<tile> tiles;

void preInit() {
    swl.load_font = true;
    swl.font_path = "../Resources/arial.ttf";
    swl.font_size = 32;
    
    swl.goFullscreen();
    SDL_ShowCursor(SDL_DISABLE);
    swl.enableVsync();
}

void postInit() {
    jd::init();
    swl.switchScene(main_scene);
    tiles = {
        tile({255, 0 ,0}, "turn off"),
        tile({0, 255, 0}, "tile1"),
        tile({255, 255, 0}, "tile2"),
        tile({0, 0, 255}, "tile3"),
        tile({255, 0, 255}, "tile4"),
        tile({0, 255, 255}, "tile5"),
        tile({255, 255, 255}, "tile6"),
    };
    for(tile& iter : tiles)
        iter.renderText();
    
    selection_rect.w = TILE_SIZE + TILE_SPACING;
    selection_rect.h = TILE_SIZE + TILE_SPACING;
    selection_rect.y = swl.window_height / 2 - selection_rect.h / 2;
    selection_rect.c = {100, 100, 100};
}

void main_event(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        swl.stop();
    else if(jd::handleEvents(event));
    else if(event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == jd::button::cross && !selected)
        swl.stop();
}

void main() {
    static bool prev_still = true;
    if(!jd::left_axis_x) {
        axis_position = to_go;
        prev_still = true;
    }
    else {
        axis_position += prev_still && jd::left_axis_x > 0 ? TILE_SIZE + TILE_SPACING : jd::left_axis_x / AXIS_SENSITIVITY;
        prev_still = false;
    }
    if(axis_position < 0)
        axis_position = 0;
    else if(axis_position > (TILE_SIZE + TILE_SPACING) * (tiles.size() - 1))
        axis_position = (TILE_SIZE + TILE_SPACING) * (unsigned int)(tiles.size() - 1);
    
    selected = axis_position / (TILE_SIZE + TILE_SPACING);
    to_go = selected * (TILE_SIZE + TILE_SPACING);
    position = abs(position - to_go) < DIVIDER ? to_go : position + (to_go - position) / DIVIDER;
    
    selection_rect.x = swl.window_width / 2 - selection_rect.w / 2 + to_go - position;
    swl.draw(selection_rect);
    
    for(unsigned int i = 0; i < tiles.size(); i++)
        tiles.at(i).render(i);
}
