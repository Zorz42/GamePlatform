//
//  gameLoader.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 27/10/2020.
//

#include "gameLoader.h"
#include "fileSystem.h"
#include "swl.h"
#include "tiles.h"
#include "mainScreen.h"
#include <fstream>
#include <map>

std::pair<bool, gameLoader::game> gameLoader::loadGame(std::string path) {
    game result;
    path.push_back('/');
    
    std::map<std::string, std::string> info;
    std::ifstream info_file(path + "Info.data");
    if(!info_file.is_open())
        return {false, result};
    
    std::string line;
    while(getline(info_file, line)) {
        std::string key, value;
        bool pushing_to_key = true;
        for(unsigned int i = 0; i < line.size(); i++) {
            if(pushing_to_key) {
                if(line[i] == ':')
                   pushing_to_key = false;
                else
                   key.push_back(line[i]);
            }
            else {
                value.push_back(line[i]);
            }
        }
        info[key] = value;
    }
    
    if(info.find("Name") == info.end() || info.find("Exec") == info.end())
        return {false, result};
    
    result.name = info["Name"];
    result.exec_path = info["Exec"];
    result.dir_path = path;
    if(info.find("Icon") != info.end())
        result.icon_path = info["Icon"];
    
    return {true, result};
}


void gameLoader::game::loadImage() {
    if(std::filesystem::is_regular_file(dir_path + icon_path))
        _icon_texture.loadFromImage(dir_path + icon_path);
    else
        _icon_texture.loadFromImage("../Resources/no-icon.jpg");
}

void gameLoader::game::renderText() {
    _text_texture.loadFromText(name, {255, 255, 255}, true);
    _text_texture.x = swl.window_width / 2 - _text_texture.w / 2;
    _text_texture.y = swl.window_height / 2 + TILE_SIZE / 2 + TILE_SPACING / 4 * 3;
}

void gameLoader::game::render(unsigned int index, float scale, int position, int selected) {
    _icon_texture.w = TILE_SIZE * scale;
    _icon_texture.h = TILE_SIZE * scale;
    _icon_texture.x = swl.window_width / 2 - _icon_texture.w / 2 + index * (_icon_texture.w + TILE_SPACING * scale) - position * scale;
    _icon_texture.y = swl.window_height / 2 - _icon_texture.h / 2;
    swl.draw(_icon_texture);
    if(mainScreen::on_tiles && index == selected)
        swl.draw(_text_texture);
}
