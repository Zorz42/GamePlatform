//
//  gameReader.h
//  GamePlatform
//
//  Created by Jakob Zorz on 27/10/2020.
//

#include <iostream>
#include <vector>

namespace gameReader {
class game {
public:
    std::string name;
};

std::pair<bool, game> loadGame(std::string path);

}
