//
//  gameReader.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 27/10/2020.
//

#include "gameReader.h"
#include "fileSystem.h"
#include <fstream>
#include <map>

std::pair<bool, gameReader::game> gameReader::loadGame(std::string path) {
    game result;
    path = path + "/";
    
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
    
    if(info.find("Name") == info.end())
        return {false, result};
    
    result.name = info["Name"];
    return {true, result};
}

