//
//  tiles.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 25/10/2020.
//

#include "tiles.h"
#include "joystickDriver.h"
#include "mainScreen.h"
#include "selectionRect.h"
#include "gameReader.h"
#include "fileSystem.h"
#include <vector>
#include <filesystem>

std::vector<gameReader::game> games;
int position = 0, selected = 0;
float scale = 1, scale_to_go = scale;

void tiles::init() {
    for (const auto& entry : std::filesystem::directory_iterator(fileSystem::root + "Games")) {
        std::pair<bool, gameReader::game> result = gameReader::loadGame(entry.path());
        if(!result.first)
            std::cout << "Error loading " << entry.path() << std::endl;
        else {
            games.emplace_back(result.second);
            games.back().renderText();
            games.back().loadImage();
        }
    }
}

bool tiles::handleEvents(SDL_Event &event) {
    return false;
}

void tiles::render() {
    static bool prev_active = false, prev_still = true, waiting_axis = false, waiting_axis_movement = false;
    static int velocity = INITIAL_VELOCITY, axis_position = 0, to_go = 0;
    
    scale = (scale + scale_to_go) / 2;
    
    if(mainScreen::on_tiles) {
        if(!prev_active) {
            scale_to_go = 1;
            selectionRect::w = TILE_SIZE + TILE_SPACING;
            selectionRect::h = TILE_SIZE + TILE_SPACING;
            selectionRect::y = swl.window_height / 2 - selectionRect::h / 2;
            selectionRect::corner_radius = TILE_SPACING;
            waiting_axis = true;
            waiting_axis_movement = true;
        }
        prev_active = true;
        if(!jd::left_axis_x) {
            if(!waiting_axis_movement)
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
            if(!waiting_axis)
                waiting_axis_movement = false;
        }
        if(axis_position < 0)
            axis_position = 0;
        else if(axis_position > (TILE_SIZE + TILE_SPACING) * (games.size() - 1) && !waiting_axis_movement)
            axis_position = (TILE_SIZE + TILE_SPACING) * (int)(games.size() - 1);
        
        selected = axis_position / (TILE_SIZE + TILE_SPACING);
        to_go = selected * (TILE_SIZE + TILE_SPACING);
        if(position != to_go)
            position += abs(position - to_go) < DIVIDER ? (position > to_go ? 1 : -1) : (to_go - position) / DIVIDER;
        selectionRect::x = swl.window_width / 2 - selectionRect::w / 2 + to_go - position;
        if(!waiting_axis_movement)
            selectionRect::teleport();
        
        if(!waiting_axis && jd::left_axis_y < -30000)
            mainScreen::on_tiles = false;
    }
    else {
        scale_to_go = .75;
        prev_active = false;
    }
    
    for(unsigned int i = 0; i < games.size(); i++)
        games.at(i).render(i, scale, position, selected);
}
