#include <vector>
#include "swl.h"
#include "joystickDriver.h"

void main();
void main_event(SDL_Event& event);
Swl::scene main_scene(&main, &main_event);

#define TILE_SIZE 500
#define TILE_SPACING 100
#define DIVIDER 5
#define AXIS_SENSITIVITY 640 // lower it is, more it is sensitive


int axis_position = 0, to_go = 0, position = 0;

struct tile {
    Swl::color color;
    void render(unsigned int index);
};

void tile::render(unsigned int index) {
    Swl::rect draw_rect;
    draw_rect.w = TILE_SIZE;
    draw_rect.h = TILE_SIZE;
    draw_rect.x = swl.window_width / 2 - draw_rect.w / 2 + index * (draw_rect.w + TILE_SPACING) - position;
    draw_rect.y = swl.window_height / 2 - draw_rect.h / 2;
    swl.setDrawColor(color);
    swl.draw(draw_rect);
}

std::vector<tile> tiles;

void preInit() {
    swl.load_font = true;
    swl.font_path = "../Resources/arial.ttf";
    swl.font_size = 32;
    
    //swl.goFullscreen();
    SDL_ShowCursor(SDL_DISABLE);
    swl.enableVsync();
}

void postInit() {
    jd::init();
    swl.switchScene(main_scene);
    tiles = {{255, 0 ,0}, {0, 255, 0}, {255, 255, 0}, {0, 0, 255}, {255, 0, 255}, {0, 255, 255}, {255, 255, 255}};
}

void main_event(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        swl.stop();
    else
        jd::handleEvents(event);
    
    if(event.type == SDL_JOYBUTTONDOWN) {
        switch(event.jbutton.button) {
            case jd::button::select:
                std::cout << "select" << std::endl;
                break;
            case jd::button::left_axis:
                std::cout << "left_axis" << std::endl;
                break;
            case jd::button::right_axis:
                std::cout << "right_axis" << std::endl;
                break;
            case jd::button::start:
                std::cout << "start" << std::endl;
                break;
            case jd::button::up:
                std::cout << "up" << std::endl;
                break;
            case jd::button::right:
                std::cout << "right" << std::endl;
                break;
            case jd::button::down:
                std::cout << "down" << std::endl;
                break;
            case jd::button::left:
                std::cout << "left" << std::endl;
                break;
            case jd::button::l1:
                std::cout << "l1" << std::endl;
                break;
            case jd::button::l2:
                std::cout << "l2" << std::endl;
                break;
            case jd::button::r1:
                std::cout << "r1" << std::endl;
                break;
            case jd::button::r2:
                std::cout << "r2" << std::endl;
                break;
            case jd::button::triangle:
                std::cout << "triangle" << std::endl;
                break;
            case jd::button::circle:
                std::cout << "circle" << std::endl;
                break;
            case jd::button::cross:
                std::cout << "cross" << std::endl;
                break;
            case jd::button::rectangle:
                std::cout << "rectangle" << std::endl;
                break;
            case jd::button::logo:
                std::cout << "logo" << std::endl;
                break;
            default:
                std::cout << "Unknown key index: " << (int)event.jbutton.button << std::endl;
        }
    }
}

void main() {
    static bool prev_still = true;
    if(!jd::left_axis_x) {
        axis_position = to_go;
        prev_still = true;
    }
    else {
        if(prev_still && jd::left_axis_x > 0)
            axis_position += TILE_SIZE + TILE_SPACING;
        else
            axis_position += jd::left_axis_x / AXIS_SENSITIVITY;
        prev_still = false;
    }
    if(axis_position < 0)
        axis_position = 0;
    else if(axis_position > (TILE_SIZE + TILE_SPACING) * (tiles.size() - 1))
        axis_position = (TILE_SIZE + TILE_SPACING) * (unsigned int)(tiles.size() - 1);
    to_go = axis_position / (TILE_SIZE + TILE_SPACING) * (TILE_SIZE + TILE_SPACING);
    if(abs(position - to_go) < DIVIDER)
        position = to_go;
    else
        position += (to_go - position) / DIVIDER;
    
    
    for(unsigned int i = 0; i < tiles.size(); i++)
        tiles.at(i).render(i);
}
