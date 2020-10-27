//
//  fileSystem.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 27/10/2020.
//

#include <sys/stat.h>
#include "fileSystem.h"
#include <filesystem>

void createDirIfExists(std::string path) {
    if(!std::filesystem::is_directory(path) && std::filesystem::create_directory(path) != 1)
        std::cout << "Warning: could not create \"" << path << "\" directory!" << std::endl;
}

void fileSystem::init() {
    root = std::string(getenv("HOME")) + "/Library/Application Support/Game Platform/";
    resource_dir = "../Resources/";
    
    std::string dirs_to_create[] = {
        "",
        "Games",
    };
    for(std::string& dir : dirs_to_create)
        createDirIfExists(root + dir);
}
